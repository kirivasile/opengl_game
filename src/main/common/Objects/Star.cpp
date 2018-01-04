#pragma once
#include "Star.h"

Star::Star(float radius, const glm::vec3& position, const std::string& texture, LightInfo light) : 
	_light{ light }
{
	_mesh = makeSphere(radius);
	_mesh->setModelMatrix(glm::translate(glm::mat4(1.0f), position));
	_position = position;
	_texture = loadTexture(texture);
	_shader = std::make_shared<ShaderProgram>("star.vert", "star.frag");
}

LightInfo Star::getLight() {
	return _light;
}

void Star::render(const CameraInfo& camera, const GLuint& sampler) {
	_shader->use();
	_shader->setMat4Uniform("viewMatrix", camera.viewMatrix);
	_shader->setMat4Uniform("projectionMatrix", camera.projMatrix);
	_shader->setMat4Uniform("modelMatrix", _mesh->modelMatrix());

	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, sampler);
	_texture->bind();
	_shader->setIntUniform("starTex", 0);

	_mesh->draw();

	glBindSampler(0, 0);
	glUseProgram(0);
}

void Star::rotate(float degrees, glm::vec3 direction) {
	_mesh->setModelMatrix(glm::rotate(_mesh->modelMatrix(), degrees, direction));
}
