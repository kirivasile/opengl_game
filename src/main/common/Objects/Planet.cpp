#pragma once
#include "Planet.h"

Planet::Planet(float radius, const glm::vec3& position, const std::string& texture, MaterialInfo material, StarPtr star) : 
	_material{ material },
	_star{ star }
{
	_mesh = makeSphere(radius);
	_mesh->setModelMatrix(glm::translate(glm::mat4(1.0f), position));
	_position = position;
	_texture = loadTexture(texture);
	_shader = std::make_shared<ShaderProgram>("planet.vert", "planet.frag");
}

MaterialInfo Planet::getMaterial() {
	return _material;
}

void Planet::render(const CameraInfo& camera, const GLuint& sampler) {
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
	glBindSampler(0, sampler);
	_texture->bind();
	_shader->setIntUniform("planetTex", 0);

	_mesh->draw();

	glBindSampler(0, 0);
	glUseProgram(0);
}

void Planet::rotate(float degrees, glm::vec3 direction) {
	_mesh->setModelMatrix(glm::rotate(_mesh->modelMatrix(), degrees, direction));
}

void Planet::rotateAroundObject(SceneObjectPtr object, float degrees, glm::vec3 direction) {
	glm::vec3 thisToObject = object->getPosition() - this->getPosition();
	glm::vec3 newThisToObject = glm::rotate(thisToObject, degrees, direction);
	glm::vec3 diff = thisToObject - newThisToObject;
	_mesh->setModelMatrix(glm::translate(_mesh->modelMatrix(), diff));
}
