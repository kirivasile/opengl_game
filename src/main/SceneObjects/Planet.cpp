#pragma once
#include "Planet.h"

Planet::Planet(
	float radius, 
	const glm::vec3& position, 
	const std::string& texture, 
	MaterialInfo material, 
	StarPtr star,
	float rotationSpeed,
	const GLuint& sampler
) : 
	_material{ material },
	_star{ star }
{
	_mesh = makeSphere(radius);
	_mesh->setModelMatrix(glm::translate(glm::mat4(1.0f), position));
	_texture = loadTexture(texture);
	_shader = std::make_shared<ShaderProgram>("planet.vert", "planet.frag");

	_position = position;
	_rotationSpeed = rotationSpeed;
	_sampler = sampler;
}

MaterialInfo Planet::getMaterial() {
	return _material;
}

void Planet::render(const CameraInfo& camera) {
	_shader->use();
	_shader->setMat4Uniform("viewMatrix", camera.viewMatrix);
	_shader->setMat4Uniform("projectionMatrix", camera.projMatrix);
	_shader->setMat4Uniform("modelMatrix", _mesh->modelMatrix());
	_shader->setMat3Uniform("normalToCameraMatrix", glm::transpose(glm::inverse(glm::mat3(camera.viewMatrix * _mesh->modelMatrix()))));

	// Setup light parameters
	_shader->setVec3Uniform("lightPosition", _star->getPosition());
	_shader->setVec3Uniform("light.La", _star->getLight().ambient);
	_shader->setVec3Uniform("light.Ld", _star->getLight().diffuse);
	_shader->setVec3Uniform("light.Ls", _star->getLight().specular);

	// Setup material parameters
	_shader->setVec3Uniform("material.Ka", _material.ambient);
	_shader->setVec3Uniform("material.Kd", _material.diffuse);
	_shader->setVec3Uniform("material.Ks", _material.specular);

	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, _sampler);
	_texture->bind();
	_shader->setIntUniform("planetTex", 0);

	_mesh->draw();

	glBindSampler(0, 0);
	glUseProgram(0);
}

void Planet::rotate() {
	_mesh->setModelMatrix(glm::rotate(_mesh->modelMatrix(), _rotationSpeed, _rotationDirection));
}
