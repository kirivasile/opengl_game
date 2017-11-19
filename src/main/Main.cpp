#include "Application.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "PerlinNoise.h"

#include <iostream>
#include <vector>

class TestApplication : public Application {
public:
	void makeScene() override {

		Application::makeScene();

		_cameraMover = std::make_shared<FreeCameraMover>();

		_terrain = makeRelief(2.f, 200U, 5, 1);
		_terrain->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.5f)));

		_shader = std::make_shared<ShaderProgram>("mainData/shader.vert", "mainData/shader.frag");	
	}

	void draw() override {
		Application::draw();

		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);

		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_shader->use();
		_shader->setMat4Uniform("viewMatrix", _camera.viewMatrix);
		_shader->setMat4Uniform("projectionMatrix", _camera.projMatrix);
		_shader->setMat4Uniform("modelMatrix", _terrain->modelMatrix());

		_terrain->draw();
	}

protected:
	MeshPtr _terrain;
	ShaderProgramPtr _shader;
};

int main() {
	TestApplication app;
	app.start();
	
	return 0;
}