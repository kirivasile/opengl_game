#pragma once
#include "BillBoard.h"

Billboard::Billboard(const glm::vec3& position, float size, const GLuint& sampler) :
	_size(size)
{
	_position = position;
	_mesh = makeQuad(size);
	_mesh->setModelMatrix(glm::translate(glm::mat4(1.0f), position));
	_shader = std::make_shared<ShaderProgram>("billboard.vert", "billboard.frag");
	_sampler = sampler;
}

void Billboard::render(const CameraInfo& camera) {
	_time += _dt;

	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	_shader->use();
	_shader->setMat4Uniform("viewMatrix", camera.viewMatrix);
	_shader->setMat4Uniform("projectionMatrix", camera.projMatrix);
	_shader->setMat4Uniform("modelMatrix", _mesh->modelMatrix());

	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, _sampler);
	_shader->setFloatUniform("time", _time);
	_shader->setVec3Uniform("centerPosition", _position);

	_mesh->draw();

	glBindSampler(0, 0);
	glUseProgram(0);

	// Disable transparency
	glDisable(GL_BLEND);
}