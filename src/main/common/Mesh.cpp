#include "Mesh.hpp"
#include "PerlinNoise.h"

#include <iostream>
#include <vector>
#include <exception>
#include <map>
#include <functional>
#include <numeric>

typedef std::vector<std::vector<std::vector<std::pair<int, glm::vec3>>>> norm_data;

MeshPtr makeRelief(float size, unsigned int frequency, int num_octvaes, float persistence) {
	std::vector<glm::vec3> vertices;
	// Array to count interpolated normals
	// By indexes it returns array of non-interpolated normals of this point
	// and iterator to store where to store this data
	norm_data norm_ij(frequency + 2,
		std::vector<std::vector<std::pair<int, glm::vec3>>>(frequency + 2, std::vector<std::pair<int, glm::vec3>>()));
	// Interpolated normals
	std::vector<glm::vec3> normals;

	std::vector<glm::vec2> tex_coords;
	std::vector<glm::vec2> map_coords;

	// Array to average normals
	std::vector<std::vector<glm::vec3>> normals_buf;

	PerlinNoise pn = PerlinNoise(num_octvaes, persistence);

	// Draw square from -size to size with frequency=frequency
	float step = 2.f / frequency;
	float shakalnost = 5.f; // Shakalnost
	int it = 0;
	int ii = 0;
	int jj = 0;
	for (float i = -1., ii = 0; i < 1.; i += step, ++ii) {
		for (float j = -1., jj = 0; j < 1.; j += step, ++jj) {
			// Frist triangle
			glm::vec3 first = glm::vec3(i * size, j * size, pn.perlin_noise_2D(i, j));
			glm::vec3 second = glm::vec3((i + step) * size, j * size, pn.perlin_noise_2D(i + step, j));
			glm::vec3 third = glm::vec3(i * size, (j + step) * size, pn.perlin_noise_2D(i, j + step));
			vertices.push_back(first);
			vertices.push_back(second);
			vertices.push_back(third);

			// Calculate normal
			glm::vec3 norm = glm::normalize(glm::cross(third - first, second - first));
			norm_ij[ii][jj].push_back(std::make_pair(it++, -norm));
			norm_ij[ii + 1][jj].push_back(std::make_pair(it++, -norm));
			norm_ij[ii][jj + 1].push_back(std::make_pair(it++, -norm));

			float tx = (i + 1.f) * shakalnost;
			float ty = (j + 1.f) * shakalnost;
			tex_coords.push_back(glm::vec2(tx, ty));
			tex_coords.push_back(glm::vec2(tx + step * shakalnost, ty));
			tex_coords.push_back(glm::vec2(tx, ty + step * shakalnost));
			// Coordinates for map texture
			float x = (i + 1.f) / 2.f;
			float y = (j + 1.f) / 2.f;
			map_coords.push_back(glm::vec2(x, y));
			map_coords.push_back(glm::vec2(x + step / 2.f, y));
			map_coords.push_back(glm::vec2(x, y + step / 2.f));

			// Second triangle
			first = glm::vec3(i * size, (j + step) * size, pn.perlin_noise_2D(i, j + step));
			second = glm::vec3((i + step) * size, (j + step) * size, pn.perlin_noise_2D(i + step, j + step));
			third = glm::vec3((i + step) * size, j * size, pn.perlin_noise_2D(i + step, j));
			vertices.push_back(first);
			vertices.push_back(second);
			vertices.push_back(third);

			norm = glm::normalize(glm::cross(third - first, second - first));
			norm_ij[ii][jj + 1].push_back(std::make_pair(it++, norm));
			norm_ij[ii + 1][jj + 1].push_back(std::make_pair(it++, norm));
			norm_ij[ii + 1][jj].push_back(std::make_pair(it++, norm));

			tex_coords.push_back(glm::vec2(tx, ty + step * shakalnost));
			tex_coords.push_back(glm::vec2(tx + step * shakalnost, ty + step * shakalnost));
			tex_coords.push_back(glm::vec2(tx + step * shakalnost, ty));
			map_coords.push_back(glm::vec2(x, y + step / 2.f));
			map_coords.push_back(glm::vec2(x + step / 2.f, y + step / 2.f));
			map_coords.push_back(glm::vec2(x + step / 2.f, y));
		}
	}

	// Find interpolated normals
	normals = std::vector<glm::vec3>(it);
	for (int ii = 0; ii < frequency + 1; ++ii) {
		for (int jj = 0; jj < frequency + 1; ++jj) {
			glm::vec3 norm;
			for (auto& elem : norm_ij[ii][jj]) {
				norm += elem.second;
			}
			norm /= norm_ij[ii][jj].size();
			for (auto& elem : norm_ij[ii][jj]) {
				normals[elem.first] = norm;
			}
		}
	}

	DataBufferPtr buf0 = std::make_shared<DataBuffer>(GL_ARRAY_BUFFER);
	buf0->setData(vertices.size() * sizeof(float) * 3, vertices.data());

	DataBufferPtr buf1 = std::make_shared<DataBuffer>(GL_ARRAY_BUFFER);
	buf1->setData(normals.size() * sizeof(float) * 3, normals.data());

	DataBufferPtr buf2 = std::make_shared<DataBuffer>(GL_ARRAY_BUFFER);
	buf2->setData(tex_coords.size() * sizeof(float) * 2, tex_coords.data());

	DataBufferPtr buf3 = std::make_shared<DataBuffer>(GL_ARRAY_BUFFER);
	buf3->setData(map_coords.size() * sizeof(float) * 2, map_coords.data());

	MeshPtr mesh = std::make_shared<Mesh>();
	mesh->setAttribute(0, 3, GL_FLOAT, GL_FALSE, 0, 0, buf0);
	mesh->setAttribute(1, 3, GL_FLOAT, GL_FALSE, 0, 0, buf1);
	mesh->setAttribute(2, 2, GL_FLOAT, GL_FALSE, 0, 0, buf2);
	mesh->setAttribute(3, 2, GL_FLOAT, GL_FALSE, 0, 0, buf3);
	mesh->setPrimitiveType(GL_TRIANGLES);
	mesh->setVertexCount(vertices.size());

	return mesh;
}
