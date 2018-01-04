#pragma once
#include "Objects\CubeObject.h"

class SkyBox : public CubeObject {
public:
	SkyBox(const float& size, const std::string& texture);

	void render(const CameraInfo& camera, const GLuint& sampler) override;

	void rotate(float degrees, glm::vec3 direction) override;
};

typedef std::shared_ptr<SkyBox> SkyBoxPtr;
