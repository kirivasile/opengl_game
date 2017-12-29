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

	LightInfo getLight();
protected:
	LightInfo _light;
};

typedef std::shared_ptr<Star> StarPtr;