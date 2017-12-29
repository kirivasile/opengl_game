#pragma once
#include "Objects\CubeObject.h"

class SkyBox : public CubeObject {
public:
	SkyBox(const float& size, const std::string& texture);

	void render(const CameraInfo& camera, const GLuint& sampler) override;
};

typedef std::shared_ptr<SkyBox> SkyBoxPtr;
