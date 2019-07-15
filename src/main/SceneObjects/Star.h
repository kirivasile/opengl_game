#pragma once
#include "Base\SceneObject.hpp"
#include "Base\IRenderable.hpp"
#include "Base\IRotatable.hpp"
#include "..\Utils\MeshFactory.h"

struct LightInfo {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Star : public SceneObject, public IRenderable, public IRotatable {
public:
	Star(
		float radius, 
		const glm::vec3& position, 
		const std::string& texture, 
		LightInfo light, 
		float rotateSpeed,
		const GLuint& sampler
	);

	void render(const CameraInfo& camera) override;

	void rotate() override;

	LightInfo getLight();
protected:
	LightInfo _light;

	float _time = 0.f;
	float _dt = 0.002f;
};

typedef std::shared_ptr<Star> StarPtr;
