#pragma once
#include "Framebuffer.hpp"

class StarScene {
public:
	StarScene(int width, int height);

	FramebufferPtr getOriginalBuffer();

	FramebufferPtr getBlurredBuffer();
protected:
	int _width, _height;
	FramebufferPtr _original, _blurred;
};

typedef std::shared_ptr<StarScene> StarScenePtr;
