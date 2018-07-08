#pragma once
#include "SphereObject.h"
#include "Framebuffer.hpp"
#include "StarScene.h"
#include <cmath>

class Billboard : public SceneObject {
public:
	Billboard(const glm::vec3& position, float size);

	void render(const CameraInfo& camera, const GLuint& sampler) override;

	void rotate(float degrees, glm::vec3 direction) override;
protected:
	MeshPtr makeQuad(float size, float N=100);

	float _size = 0.f;
	float _time = 0.f;
	float _dt = 0.002f;
	float _PERIOD = 1.f;
};

typedef std::shared_ptr<Billboard> BillboardPtr;