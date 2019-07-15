#pragma once
#include "..\OpenGL\Mesh.hpp"
#include "..\OpenGL\ShaderProgram.hpp"
#include "..\OpenGL\Texture.hpp"
#include "..\OpenGL\Camera.hpp"
#include "Base\IRotatable.hpp"
#include "Base\IRenderable.hpp"
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
protected:
	glm::vec3 _position{ glm::vec3(0.f, 0.f, 0.f) };
	MeshPtr _mesh;
	ShaderProgramPtr _shader;
	TexturePtr _texture;

};

typedef std::shared_ptr<SceneObject> SceneObjectPtr;