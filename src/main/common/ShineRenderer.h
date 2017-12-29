#pragma once
#include <vector>
#include "Objects\SceneObject.hpp"
#include "Camera.hpp"
#include "Framebuffer.hpp"
#include "Objects\ScreenQuad.hpp"

class ShineRenderer {
	/*
	Adds shine effect to all bright objects on the screen
	*/
public:
	ShineRenderer(int width, int height);

	void render(const std::vector<SceneObjectPtr>& objects, const std::vector<GLuint>& samplers, const CameraInfo& camera);

	void resize(int width, int height);
protected:
	FramebufferPtr _original, _hor_blurred, _ver_blurred;
	ShaderProgramPtr _blurredShader, _mainShader;
	ScreenQuadPtr _quad;

	int _width, _height;
};

typedef std::shared_ptr<ShineRenderer> ShineRendererPtr;
