#include "OpenGL\Application.hpp"
#include "OpenGL\ScreenQuad.hpp"
#include "SceneObjects\Star.h"
#include "SceneObjects\Planet.h"
#include "SceneObjects\SkyBox.h"
#include "SceneObjects\Billboard.h"

class Game : public Application {
public:
	void makeScene() override {

		Application::makeScene();

		initSamplers();

		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);

		// Init camera controller
		_cameraMover = std::make_shared<FreeCameraMover>();
		
		// Init sun
		glm::vec3 sunPosition = glm::vec3(0.0f, -5.0f, 0.f);
		LightInfo sunLight;
		sunLight.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		sunLight.diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
		sunLight.specular = glm::vec3(0.2f, 0.2f, 0.2f);

		float sunRadius = 1.f;
		float sunRotateSpeed = 5e-4f;
		_sun = std::make_shared<Star>(
			sunRadius, 
			sunPosition, 
			"sun.jpg", 
			sunLight, 
			sunRotateSpeed,
			_sampler
		);

		// Sun corona
		_corona = std::make_shared<Billboard>(sunPosition, 4.0f, _sampler);

		// Init earth
		glm::vec3 earthPosition = glm::vec3(5.0f, -5.0f, 0.f);
		MaterialInfo earthMaterial;
		earthMaterial.ambient = glm::vec3(1.f, 1.f, 1.f);
		earthMaterial.diffuse = glm::vec3(1.f, 1.f, 1.f);
		earthMaterial.specular = glm::vec3(1.f, 1.f, 1.f);

		float earthRadius = 0.4f;
		float earthRotationSpeed = 1e-4f;
		_earth = std::make_shared<Planet>(
			earthRadius, 
			earthPosition, 
			"earth.jpg", 
			earthMaterial, 
			_sun,
			earthRotationSpeed,
			_sampler
		);

		// Init skybox
		_skyBox = std::make_shared<SkyBox>(10.f, "skybox", _skyBoxSampler);

		_renderableObjects = { _earth, _sun, _skyBox, _corona };
		_rotatableObjects = { _earth, _sun };
	}

	void initSamplers() {
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
		/*
		Method will be called every frame
		*/

		Application::draw();

		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendering all objects
		for (auto &obj : _renderableObjects) {
			obj->render(_camera);
		}

		// Rotating all objects
		for (auto &obj : _rotatableObjects) {
			obj->rotate();
		}
	}

protected:
	StarPtr _sun;
	BillboardPtr _corona;
	PlanetPtr _earth;
	SkyBoxPtr _skyBox;

	std::vector<IRotatablePtr> _rotatableObjects;
	std::vector<IRenderablePtr> _renderableObjects;

	GLuint _sampler, _skyBoxSampler;
};

int main() {
	Game app;
	app.start();
	
	return 0;
}