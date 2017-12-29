#pragma once
#include "SceneObject.hpp"

class CubeObject : public SceneObject {
protected:
	MeshPtr makeCube(const float& size);
};
