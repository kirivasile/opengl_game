#pragma once
#include <glm/glm.hpp>
#include "SphereObject.h"
#include "Star.h"

struct MaterialInfo {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Planet : public SphereObject {
public:
	Planet(float radius, const glm::vec3& position, const std::string& texture, MaterialInfo material, StarPtr star);

	void render(const CameraInfo& camera, const GLuint& sampler) override;

	MaterialInfo getMaterial();
protected:
	MaterialInfo _material;
	StarPtr _star;
};

typedef std::shared_ptr<Planet> PlanetPtr;
