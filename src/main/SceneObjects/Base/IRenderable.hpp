#pragma once
#include "..\OpenGL\Camera.hpp"
#include <glm/glm.hpp>

class IRenderable {
public:
	virtual void render(const CameraInfo& camera) = 0;
protected:
	GLuint _sampler;
};

typedef std::shared_ptr<IRenderable> IRenderablePtr;