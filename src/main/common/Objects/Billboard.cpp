#pragma once
#include "BillBoard.h"

Billboard::Billboard(const glm::vec3& position, float size) :
	_size(size)
{
	_position = position;
	_mesh = makeQuad(size);
	_mesh->setModelMatrix(glm::translate(glm::mat4(1.0f), position));
	//_texture = loadTexture(texture);
	_shader = std::make_shared<ShaderProgram>("billboard.vert", "billboard.frag");
}

MeshPtr Billboard::makeQuad(float size, float N) {
	// TODO: size
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	for (float i = -N; i < N; i += 1.f) {
		for (float j = -N; j < N; j += 1.f) {
			vertices.push_back(glm::vec3(size * (i / N), size * ((j + 1) / N), 0.0));
			vertices.push_back(glm::vec3(size * ((i + 1) / N), size * (j / N), 0.0));
			vertices.push_back(glm::vec3(size * ((i + 1) / N), size * ((j + 1) / N), 0.0));

			// TODO: fix from [-1; 1] to [0; 1]
			texCoords.push_back(glm::vec2(i / N, (i + 1) / N));
			texCoords.push_back(glm::vec2((i + 1) / N, i / N));
			texCoords.push_back(glm::vec2((i + 1) / N, (i + 1) / N));

			//front 2
			vertices.push_back(glm::vec3(size * (i / N), size * ((j + 1) / N), 0.0));
			vertices.push_back(glm::vec3(size * (i / N), size * (j / N), 0.0));
			vertices.push_back(glm::vec3(size * ((i + 1) / N), size * (j / N), 0.0));

			texCoords.push_back(glm::vec2(i / N, (i + 1) / N));
			texCoords.push_back(glm::vec2(i / N, i / N));
			texCoords.push_back(glm::vec2((i + 1) / N, i / N));
		}
	}
	

	DataBufferPtr buf0 = std::make_shared<DataBuffer>(GL_ARRAY_BUFFER);
	buf0->setData(vertices.size() * sizeof(float) * 3, vertices.data());

	DataBufferPtr buf1 = std::make_shared<DataBuffer>(GL_ARRAY_BUFFER);
	buf1->setData(texCoords.size() * sizeof(float) * 2, texCoords.data());

	MeshPtr mesh = std::make_shared<Mesh>();
	mesh->setAttribute(0, 3, GL_FLOAT, GL_FALSE, 0, 0, buf0);
	mesh->setAttribute(1, 2, GL_FLOAT, GL_FALSE, 0, 0, buf1);
	mesh->setPrimitiveType(GL_TRIANGLES);
	mesh->setVertexCount(vertices.size());

	return mesh;
}

void Billboard::render(const CameraInfo& camera, const GLuint& sampler) {
	//_time = sinf(_time + _dt);
	_time += _dt;

	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	_shader->use();
	_shader->setMat4Uniform("viewMatrix", camera.viewMatrix);
	_shader->setMat4Uniform("projectionMatrix", camera.projMatrix);
	_shader->setMat4Uniform("modelMatrix", _mesh->modelMatrix());

	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, sampler);
	//_texture->bind();
	//_shader->setIntUniform("starTex", 0);
	_shader->setFloatUniform("time", _time);
	_shader->setVec3Uniform("centerPosition", _position);

	_mesh->draw();

	glBindSampler(0, 0);
	glUseProgram(0);

	// Disable transparency
	glDisable(GL_BLEND);
}

void Billboard::rotate(float degrees, glm::vec3 direction) {}