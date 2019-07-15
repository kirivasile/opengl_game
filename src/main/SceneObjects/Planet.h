#pragma once
#include "Base\SceneObject.hpp"
#include "Base\IRenderable.hpp"
#include "Base\IRotatable.hpp"
#include "Star.h"
#include "..\Utils\MeshFactory.h"
#include <glm/gtx/rotate_vector.hpp>

struct MaterialInfo {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Planet : public SceneObject, public IRenderable, public IRotatable {
public:
	Planet(
		float radius,
		const glm::vec3& position,
		const std::string& texture,
		MaterialInfo material,
		StarPtr star,
		float rotationSpeed,
		const GLuint& sampler
	);

	void render(const CameraInfo& camera) override;

	void rotate() override;

	MaterialInfo getMaterial();
protected:
	MaterialInfo _material;
	StarPtr _star;
};

typedef std::shared_ptr<Planet> PlanetPtr;
