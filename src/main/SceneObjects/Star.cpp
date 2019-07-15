#pragma once
#include "Star.h"

Star::Star(
	float radius, 
	const glm::vec3& position, 
	const std::string& texture, 
	LightInfo light, 
	float rotationSpeed,
	const GLuint& sampler
) : 
	_light{ light }
{
	_mesh = makeSphere(radius);
	_mesh->setModelMatrix(glm::translate(glm::mat4(1.0f), position));
	_position = position;
	_texture = loadTexture(texture);
	_shader = std::make_shared<ShaderProgram>("star.vert", "star.frag");
	_rotationSpeed = rotationSpeed;
	_sampler = sampler;
}

LightInfo Star::getLight() {
	return _light;
}

void Star::render(const CameraInfo& camera) {
	_time += _dt;

	_shader->use();
	_shader->setFloatUniform("time", _time);
	_shader->setMat4Uniform("viewMatrix", camera.viewMatrix);
	_shader->setMat4Uniform("projectionMatrix", camera.projMatrix);
	_shader->setMat4Uniform("modelMatrix", _mesh->modelMatrix());

	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, _sampler);
	_texture->bind();
	_shader->setIntUniform("starTex", 0);

	_mesh->draw();

	glBindSampler(0, 0);
	glUseProgram(0);
}

void Star::rotate() {
	_mesh->setModelMatrix(glm::rotate(_mesh->modelMatrix(), _rotationSpeed, _rotationDirection));
}
