#pragma once
#include "Base\SceneObject.hpp"
#include "Base\IRenderable.hpp"
#include "..\OpenGL\Framebuffer.hpp"
#include "..\Utils\MeshFactory.h"
#include <cmath>

class Billboard : public SceneObject, public IRenderable {
public:
	Billboard(const glm::vec3& position, float size, const GLuint& sampler);

	void render(const CameraInfo& camera) override;
protected:

	float _size = 0.f;
	float _time = 0.f;
	float _dt = 0.002f;
	float _PERIOD = 1.f;
};

typedef std::shared_ptr<Billboard> BillboardPtr;