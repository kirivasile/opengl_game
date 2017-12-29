#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <iostream>	

#include <GL/glew.h>

class Framebuffer {
protected:
	GLuint _fbo;
	GLuint _colorBuffer;
	GLuint _depthBuffer;

	void createRenderTextures(int width, int height) {
		glGenTextures(1, &_colorBuffer);
		glBindTexture(GL_TEXTURE_2D, _colorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenRenderbuffers(1, &_depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorBuffer, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "Framebuffer not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
public:
	Framebuffer(int width, int height) {
		glGenFramebuffers(1, &_fbo);
		createRenderTextures(width, height);
	}

	void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	}

	void bindColorBuffer() {
		glBindTexture(GL_TEXTURE_2D, _colorBuffer);
	}

	void unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::resize(unsigned int width, unsigned int height) {
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

		//Пробегаем по всем текстурам и по новой выделяем память под нужный размер
		/*for (const auto& kv : _textureToInternalFormat)
		{
			if (_textureToAttachment[kv.first] == GL_DEPTH_ATTACHMENT)
			{
				kv.first->setTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, _width, _height, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
			}
			else
			{
				kv.first->setTexImage2D(GL_TEXTURE_2D, 0, kv.second, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, 0);
			}
		}*/
		glBindTexture(GL_TEXTURE_2D, _colorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
};

typedef std::shared_ptr<Framebuffer> FramebufferPtr;