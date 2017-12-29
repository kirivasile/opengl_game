#include "CubeObject.h"

MeshPtr CubeObject::makeCube(const float& size) {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;

	//front 1
	vertices.push_back(glm::vec3(size, -size, size));
	vertices.push_back(glm::vec3(size, size, -size));
	vertices.push_back(glm::vec3(size, size, size));

	normals.push_back(glm::vec3(1.0, 0.0, 0.0));
	normals.push_back(glm::vec3(1.0, 0.0, 0.0));
	normals.push_back(glm::vec3(1.0, 0.0, 0.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));
	texcoords.push_back(glm::vec2(1.0, 1.0));

	//front 2
	vertices.push_back(glm::vec3(size, -size, size));
	vertices.push_back(glm::vec3(size, -size, -size));
	vertices.push_back(glm::vec3(size, size, -size));

	normals.push_back(glm::vec3(1.0, 0.0, 0.0));
	normals.push_back(glm::vec3(1.0, 0.0, 0.0));
	normals.push_back(glm::vec3(1.0, 0.0, 0.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(0.0, 0.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));

	//left 1
	vertices.push_back(glm::vec3(-size, -size, size));
	vertices.push_back(glm::vec3(size, -size, -size));
	vertices.push_back(glm::vec3(size, -size, size));

	normals.push_back(glm::vec3(0.0, -1.0, 0.0));
	normals.push_back(glm::vec3(0.0, -1.0, 0.0));
	normals.push_back(glm::vec3(0.0, -1.0, 0.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));
	texcoords.push_back(glm::vec2(1.0, 1.0));

	//left 2
	vertices.push_back(glm::vec3(-size, -size, size));
	vertices.push_back(glm::vec3(-size, -size, -size));
	vertices.push_back(glm::vec3(size, -size, -size));

	normals.push_back(glm::vec3(0.0, -1.0, 0.0));
	normals.push_back(glm::vec3(0.0, -1.0, 0.0));
	normals.push_back(glm::vec3(0.0, -1.0, 0.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(0.0, 0.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));

	//top 1
	vertices.push_back(glm::vec3(-size, size, size));
	vertices.push_back(glm::vec3(size, -size, size));
	vertices.push_back(glm::vec3(size, size, size));

	normals.push_back(glm::vec3(0.0, 0.0, 1.0));
	normals.push_back(glm::vec3(0.0, 0.0, 1.0));
	normals.push_back(glm::vec3(0.0, 0.0, 1.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));
	texcoords.push_back(glm::vec2(1.0, 1.0));

	//top 2
	vertices.push_back(glm::vec3(-size, size, size));
	vertices.push_back(glm::vec3(-size, -size, size));
	vertices.push_back(glm::vec3(size, -size, size));

	normals.push_back(glm::vec3(0.0, 0.0, 1.0));
	normals.push_back(glm::vec3(0.0, 0.0, 1.0));
	normals.push_back(glm::vec3(0.0, 0.0, 1.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(0.0, 0.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));

	//back 1
	vertices.push_back(glm::vec3(-size, -size, size));
	vertices.push_back(glm::vec3(-size, size, size));
	vertices.push_back(glm::vec3(-size, size, -size));

	normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
	normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
	normals.push_back(glm::vec3(-1.0, 0.0, 0.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));

	//back 2
	vertices.push_back(glm::vec3(-size, -size, size));
	vertices.push_back(glm::vec3(-size, size, -size));
	vertices.push_back(glm::vec3(-size, -size, -size));

	normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
	normals.push_back(glm::vec3(-1.0, 0.0, 0.0));
	normals.push_back(glm::vec3(-1.0, 0.0, 0.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));
	texcoords.push_back(glm::vec2(0.0, 0.0));

	//right 1
	vertices.push_back(glm::vec3(-size, size, size));
	vertices.push_back(glm::vec3(size, size, size));
	vertices.push_back(glm::vec3(size, size, -size));

	normals.push_back(glm::vec3(0.0, 1.0, 0.0));
	normals.push_back(glm::vec3(0.0, 1.0, 0.0));
	normals.push_back(glm::vec3(0.0, 1.0, 0.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));

	//right 2
	vertices.push_back(glm::vec3(-size, size, size));
	vertices.push_back(glm::vec3(+size, size, -size));
	vertices.push_back(glm::vec3(-size, size, -size));

	normals.push_back(glm::vec3(0.0, 1.0, 0.0));
	normals.push_back(glm::vec3(0.0, 1.0, 0.0));
	normals.push_back(glm::vec3(0.0, 1.0, 0.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));
	texcoords.push_back(glm::vec2(0.0, 0.0));

	//bottom 1
	vertices.push_back(glm::vec3(-size, size, -size));
	vertices.push_back(glm::vec3(size, size, -size));
	vertices.push_back(glm::vec3(size, -size, -size));

	normals.push_back(glm::vec3(0.0, 0.0, -1.0));
	normals.push_back(glm::vec3(0.0, 0.0, -1.0));
	normals.push_back(glm::vec3(0.0, 0.0, -1.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));

	//bottom 2
	vertices.push_back(glm::vec3(-size, size, -size));
	vertices.push_back(glm::vec3(size, -size, -size));
	vertices.push_back(glm::vec3(-size, -size, -size));

	normals.push_back(glm::vec3(0.0, 0.0, -1.0));
	normals.push_back(glm::vec3(0.0, 0.0, -1.0));
	normals.push_back(glm::vec3(0.0, 0.0, -1.0));

	texcoords.push_back(glm::vec2(0.0, 1.0));
	texcoords.push_back(glm::vec2(1.0, 0.0));
	texcoords.push_back(glm::vec2(0.0, 0.0));

	//----------------------------------------

	DataBufferPtr buf0 = std::make_shared<DataBuffer>(GL_ARRAY_BUFFER);
	buf0->setData(vertices.size() * sizeof(float) * 3, vertices.data());

	DataBufferPtr buf1 = std::make_shared<DataBuffer>(GL_ARRAY_BUFFER);
	buf1->setData(normals.size() * sizeof(float) * 3, normals.data());

	DataBufferPtr buf2 = std::make_shared<DataBuffer>(GL_ARRAY_BUFFER);
	buf2->setData(texcoords.size() * sizeof(float) * 2, texcoords.data());

	MeshPtr mesh = std::make_shared<Mesh>();
	mesh->setAttribute(0, 3, GL_FLOAT, GL_FALSE, 0, 0, buf0);
	mesh->setAttribute(1, 3, GL_FLOAT, GL_FALSE, 0, 0, buf1);
	mesh->setAttribute(2, 2, GL_FLOAT, GL_FALSE, 0, 0, buf2);
	mesh->setPrimitiveType(GL_TRIANGLES);
	mesh->setVertexCount(vertices.size());
	return mesh;
}