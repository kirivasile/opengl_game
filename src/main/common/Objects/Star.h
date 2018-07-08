#pragma once
#include "SphereObject.h"
#include "Framebuffer.hpp"
#include "StarScene.h"

struct LightInfo {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Star : public SphereObject {
public:
	Star(float radius, const glm::vec3& position, const std::string& texture, LightInfo light);

	void render(const CameraInfo& camera, const GLuint& sampler) override;

	void rotate(float degrees, glm::vec3 direction) override;

	LightInfo getLight();
protected:
	LightInfo _light;

	float _time = 0.f;
	float _dt = 0.002f;
};

typedef std::shared_ptr<Star> StarPtr;
