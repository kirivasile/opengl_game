#pragma once
#include "..\OpenGL\Mesh.hpp"

MeshPtr makeCube(const float& size);

MeshPtr makeSphere(const float& radius, unsigned int N = 100);

MeshPtr makeQuad(float size, float N = 100);