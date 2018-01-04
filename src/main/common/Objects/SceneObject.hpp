#pragma once
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include <glm/glm.hpp>

class SceneObject {
public:
	MeshPtr getMesh() const {
		return _mesh;
	}

	ShaderProgramPtr getShader() const {
		return _shader;
	}

	TexturePtr getTexture() const {
		return _texture;
	}

	glm::vec3 getPosition() const {
		return _position;
	}

	virtual void render(const CameraInfo& camera, const GLuint& sampler) = 0;

	virtual void rotate(float degrees, glm::vec3 direction) = 0;
protected:
	glm::vec3 _position{ glm::vec3(0.f, 0.f, 0.f) };
	MeshPtr _mesh;
	ShaderProgramPtr _shader;
	TexturePtr _texture;

};

typedef std::shared_ptr<SceneObject> SceneObjectPtr;