#pragma once
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Framebuffer.hpp"

class ScreenQuad {
public:
	ScreenQuad() {
		_mesh = makeQuad();
	}

	void render(ShaderProgramPtr shader, FramebufferPtr framebuffer) {
		shader->use();
		glActiveTexture(GL_TEXTURE0);
		framebuffer->bindColorBuffer();
		shader->setIntUniform("tex", 0);
		_mesh->draw();

		glBindSampler(0, 0);
		glUseProgram(0);
	}

	void draw() {
		_mesh->draw();
	}

protected:
	MeshPtr makeQuad() {
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> texCoords;

		//front 1
		vertices.push_back(glm::vec3(-1.0, 1.0, 0.0));
		vertices.push_back(glm::vec3(1.0, -1.0, 0.0));
		vertices.push_back(glm::vec3(1.0, 1.0, 0.0));

		texCoords.push_back(glm::vec2(0.0, 1.0));
		texCoords.push_back(glm::vec2(1.0, 0.0));
		texCoords.push_back(glm::vec2(1.0, 1.0));

		//front 2
		vertices.push_back(glm::vec3(-1.0, 1.0, 0.0));
		vertices.push_back(glm::vec3(-1.0, -1.0, 0.0));
		vertices.push_back(glm::vec3(1.0, -1.0, 0.0));

		texCoords.push_back(glm::vec2(0.0, 1.0));
		texCoords.push_back(glm::vec2(0.0, 0.0));
		texCoords.push_back(glm::vec2(1.0, 0.0));

		//----------------------------------------

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

	MeshPtr _mesh;
};

typedef std::shared_ptr<ScreenQuad> ScreenQuadPtr;