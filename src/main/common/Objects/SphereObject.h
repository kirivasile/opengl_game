#pragma once
#include "SceneObject.hpp"

class SphereObject : public SceneObject {
protected:
	MeshPtr makeSphere(const float& radius, unsigned int N=100);
};
