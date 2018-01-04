#pragma once
#include "SphereObject.h"
#include "Star.h"
#include <glm/gtx/rotate_vector.hpp>

struct MaterialInfo {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Planet : public SphereObject {
public:
	Planet(float radius, const glm::vec3& position, const std::string& texture, MaterialInfo material, StarPtr star);

	void render(const CameraInfo& camera, const GLuint& sampler) override;

	void rotate(float degrees, glm::vec3 direction) override;

	void rotateAroundObject(SceneObjectPtr object, float degrees, glm::vec3 direction);

	MaterialInfo getMaterial();
protected:
	MaterialInfo _material;
	StarPtr _star;
	float _rotationSpeedAroundStar{ 0.f };
};

typedef std::shared_ptr<Planet> PlanetPtr;
