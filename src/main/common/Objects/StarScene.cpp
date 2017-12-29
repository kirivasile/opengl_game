#include "StarScene.h"

StarScene::StarScene(int width, int height) : _width(width), _height(height) {
	_original = std::make_shared<Framebuffer>(width, height);
}

FramebufferPtr StarScene::getOriginalBuffer() {
	return _original;
}

FramebufferPtr StarScene::getBlurredBuffer() {
	return _blurred;
}