#pragma once
#include "Base\SceneObject.hpp"
#include "Base\IRenderable.hpp"
#include "..\Utils\MeshFactory.h"

class SkyBox : public SceneObject, public IRenderable {
public:
	SkyBox(const float& size, const std::string& texture, const GLuint& sampler);

	void render(const CameraInfo& camera) override;
};

typedef std::shared_ptr<SkyBox> SkyBoxPtr;
