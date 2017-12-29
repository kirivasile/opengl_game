#pragma once
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include <glm/glm.hpp>

class SceneObject {
public:
	MeshPtr getMesh() {
		return _mesh;
	}

	ShaderProgramPtr getShader() {
		return _shader;
	}

	TexturePtr getTexture() {
		return _texture;
	}

	glm::vec3 getPosition() {
		return _position;
	}

	virtual void render(const CameraInfo& camera, const GLuint& sampler) = 0;
protected:
	glm::vec3 _position;
	MeshPtr _mesh;
	ShaderProgramPtr _shader;
	TexturePtr _texture;
};

typedef std::shared_ptr<SceneObject> SceneObjectPtr;