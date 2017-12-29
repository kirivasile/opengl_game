#include "ShineRenderer.h"
#include <iostream>

ShineRenderer::ShineRenderer(int width, int height)
	: _width(width), _height(height){

	_original = std::make_shared<Framebuffer>(width, height);
	_hor_blurred = std::make_shared<Framebuffer>(width, height);
	_ver_blurred = std::make_shared<Framebuffer>(width, height);

	_quad = std::make_shared<ScreenQuad>();

	_blurredShader = std::make_shared<ShaderProgram>("blurred.vert", "blurred.frag");
	_mainShader = std::make_shared<ShaderProgram>("shine_main.vert", "shine_main.frag");
}

void ShineRenderer::render(const std::vector<SceneObjectPtr>& objects, const std::vector<GLuint>& samplers, const CameraInfo& camera) {
	// Render original image to texture
	_original->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (objects.size() != samplers.size()) {
		std::cerr << "ShineRenderer, incorrect vector sizes\n";
	}
	for (unsigned int i = 0; i < objects.size(); ++i) {
		objects[i]->render(camera, samplers[i]);
	}
	_original->unbind();

	// Render texture to another texture with horizontal blur
	_hor_blurred->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_blurredShader->use();
	glActiveTexture(GL_TEXTURE0);
	_original->bindColorBuffer();
	_blurredShader->setIntUniform("tex", 0);
	_blurredShader->setVec2Uniform("direction", glm::vec2(0.006, 0.0));
	_quad->draw();
	_hor_blurred->unbind();

	// Vertical blur
	_ver_blurred->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_blurredShader->use();
	glActiveTexture(GL_TEXTURE0);
	_hor_blurred->bindColorBuffer();
	_blurredShader->setIntUniform("tex", 0);
	_blurredShader->setVec2Uniform("direction", glm::vec2(0.0, 0.006));
	_quad->draw();
	_ver_blurred->unbind();

	//Render both original and blurred texture to the screen

	_mainShader->use();
	glActiveTexture(GL_TEXTURE0);
	_original->bindColorBuffer();
	_mainShader->setIntUniform("originalTex", 0);

	glActiveTexture(GL_TEXTURE0 + 1);
	_ver_blurred->bindColorBuffer();
	_mainShader->setIntUniform("blurTex", 1);

	_quad->draw();
}

void ShineRenderer::resize(int width, int height) {
	_width = width;
	_height = height;
	_original->resize(width, height);
	_hor_blurred->resize(width, height);
	_ver_blurred->resize(width, height);
}