#include "Application.hpp"
#include "Objects\Star.h"
#include "Objects\Planet.h"
#include "Objects\SkyBox.h"
#include "Objects\ScreenQuad.hpp"
#include "ShineRenderer.h"

class TestApplication : public Application {
public:
	void makeScene() override {

		Application::makeScene();

		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);
		_shineRenderer = std::make_shared<ShineRenderer>(width, height);

		_cameraMover = std::make_shared<FreeCameraMover>();
		
		// Init sun
		glm::vec3 sunPosition = glm::vec3(0.0f, -5.0f, 0.f);
		LightInfo sunLight;
		sunLight.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		sunLight.diffuse = glm::vec3(0.9f, 0.9f, 0.9f);
		sunLight.specular = glm::vec3(0.2f, 0.2f, 0.2f);
		_sun = std::make_shared<Star>(1.f, sunPosition, "sun.jpg", sunLight);

		// Init earth
		glm::vec3 earthPosition = glm::vec3(5.0f, -5.0f, 0.f);
		MaterialInfo earthMaterial;
		earthMaterial.ambient = glm::vec3(1.f, 1.f, 1.f);
		earthMaterial.diffuse = glm::vec3(1.f, 1.f, 1.f);
		earthMaterial.specular = glm::vec3(1.f, 1.f, 1.f);
		_earth = std::make_shared<Planet>(0.4f, earthPosition, "earth.jpg", earthMaterial, _sun);

		// Init skybox
		_skyBox = std::make_shared<SkyBox>(10.f, "skybox");

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

		_sceneObjects = { _earth, _sun, _skyBox};
		_samplers = { _sampler, _sampler, _skyBoxSampler };
	}

	void draw() override {
		Application::draw();

		// Rotate objects


		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//_shineRenderer->render(_sceneObjects, _samplers, _camera);

		for (unsigned int i = 0; i < _sceneObjects.size(); ++i) {
			_sceneObjects[i]->render(_camera, _samplers[i]);
		}

		_earth->rotate(5e-4f, glm::vec3(0.f, 0.f, 1.f));
		_sun->rotate(1e-4f, glm::vec3(0.f, 0.f, 1.f));
		//_earth->rotateAroundObject(_sun, 3e-2f, glm::vec3(0.f, 0.f, 1.f));
	}

	void update() override {
		Application::update();
		// If the size of the windows is changed, resize all buffers
		int width, height;
		glfwGetWindowSize(_window, &width, &height);
		if (width != _oldWidth || height != _oldHeight) {
			_shineRenderer->resize(width, height);
			_oldWidth = width;
			_oldHeight = height;
		}
	}

protected:
	StarPtr _sun;
	PlanetPtr _earth;
	SkyBoxPtr _skyBox;

	GLuint _sampler, _skyBoxSampler;

	ShineRendererPtr _shineRenderer;

	std::vector<SceneObjectPtr> _sceneObjects;
	std::vector<GLuint> _samplers;

	int _oldWidth, _oldHeight;
};

int main() {
	TestApplication app;
	app.start();
	
	return 0;
}