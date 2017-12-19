#include "Application.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <iostream>
#include <vector>

class TestApplication : public Application {
public:
	void makeScene() override {

		Application::makeScene();

		_cameraMover = std::make_shared<FreeCameraMover>();

		_skyBox = makeCube(10.f);
		_sun = makeSphere(1.f);
		_sun->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, 0.f)));
		_earth = makeSphere(0.5f);
		_earth->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, -5.0f, 0.f)));

		_starShader = std::make_shared<ShaderProgram>("star.vert", "star.frag");
		_planetShader = std::make_shared<ShaderProgram>("planet.vert", "planet.frag");
		_skyBoxShader = std::make_shared<ShaderProgram>("skybox.vert", "skybox.frag");

		_sunTex = loadTexture("sun.jpg");
		_skyBoxTex = loadCubeTexture("skybox");
		_earthTex = loadTexture("earth.jpg");

		// Initialize samplers for keeping the parameters of the reading from textures
		glGenSamplers(1, &_sampler);
		glSamplerParameteri(_sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glSamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenSamplers(1, &_skyBoxSampler);
		glSamplerParameteri(_skyBoxSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(_skyBoxSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(_skyBoxSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(_skyBoxSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(_skyBoxSampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void draw() override {
		Application::draw();

		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderStar(_sun, _sunTex);
		renderPlanet(_earth, _earthTex);
		renderSkyBox();


	}

protected:
	void renderStar(MeshPtr star, TexturePtr texture) {
		_starShader->use();
		_starShader->setMat4Uniform("viewMatrix", _camera.viewMatrix);
		_starShader->setMat4Uniform("projectionMatrix", _camera.projMatrix);
		_starShader->setMat4Uniform("modelMatrix", star->modelMatrix());

		glActiveTexture(GL_TEXTURE0);
		glBindSampler(0, _sampler);
		texture->bind();
		_starShader->setIntUniform("starTex", 0);

		star->draw();

		glBindSampler(0, 0);
		glUseProgram(0);
	}

	void renderSkyBox() {
		_skyBoxShader->use();
		// Get the position of the virtual camera in the world coordinate system from the view matrix
		glm::vec3 cameraPos = glm::vec3(glm::inverse(_camera.viewMatrix)[3]);

		_skyBoxShader->setVec3Uniform("cameraPos", cameraPos);
		_skyBoxShader->setMat4Uniform("viewMatrix", _camera.viewMatrix);
		_skyBoxShader->setMat4Uniform("projectionMatrix", _camera.projMatrix);

		// To change the coordinates into texture coordinates we need matrix to rotate YZ on 90 degrees and reflect on Y
		glm::mat3 textureMatrix = glm::mat3(glm::scale(glm::rotate(glm::mat4(), -glm::pi<float>() * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(1.0f, -1.0f, 1.0f)));
		_skyBoxShader->setMat3Uniform("textureMatrix", textureMatrix);

		glActiveTexture(GL_TEXTURE0);
		glBindSampler(0, _skyBoxSampler);
		_skyBoxTex->bind();
		_skyBoxShader->setIntUniform("skyBoxTex", 0);

		glDepthMask(GL_FALSE); //Disabling the write to the depth buffer

		_skyBox->draw();

		glDepthMask(GL_TRUE); //Enabling the write to the depth buffer

							  //Disconnect sampler and shader program
		glBindSampler(0, 0);
		glUseProgram(0);
	}

	void renderPlanet(MeshPtr planet, TexturePtr texture) {
		_planetShader->use();
		_planetShader->setMat4Uniform("viewMatrix", _camera.viewMatrix);
		_planetShader->setMat4Uniform("projectionMatrix", _camera.projMatrix);
		_planetShader->setMat4Uniform("modelMatrix", planet->modelMatrix());

		glActiveTexture(GL_TEXTURE0);
		glBindSampler(0, _sampler);
		texture->bind();
		_planetShader->setIntUniform("planetTex", 0);

		planet->draw();

		glBindSampler(0, 0);
		glUseProgram(0);
	}

	MeshPtr _sun;
	MeshPtr _earth;
	MeshPtr _skyBox;

	ShaderProgramPtr _starShader;
	ShaderProgramPtr _planetShader;
	ShaderProgramPtr _skyBoxShader;

	TexturePtr _sunTex;
	TexturePtr _earthTex;
	TexturePtr _skyBoxTex;

	GLuint _sampler;
	GLuint _skyBoxSampler;
};

int main() {
	TestApplication app;
	app.start();
	
	return 0;
}