#pragma once
#include <glm/glm.hpp>

class IRotatable {
public:
	virtual void rotate() = 0;
protected:
	float _rotationSpeed = 0.f;
	glm::vec3 _rotationDirection = glm::vec3(0.f, 0.f, 1.f);
};

typedef std::shared_ptr<IRotatable> IRotatablePtr;