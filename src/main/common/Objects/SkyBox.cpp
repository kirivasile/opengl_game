#include "SkyBox.h"

SkyBox::SkyBox(const float& size, const std::string& texture) {
	_mesh = makeCube(10.f);
	_texture = loadCubeTexture(texture);
	_shader = std::make_shared<ShaderProgram>("skybox.vert", "skybox.frag");
}

void SkyBox::render(const CameraInfo& camera, const GLuint& sampler) {
	_shader->use();
	// Get the position of the virtual camera in the world coordinate system from the view matrix
	glm::vec3 cameraPos = glm::vec3(glm::inverse(camera.viewMatrix)[3]);

	_shader->setVec3Uniform("cameraPos", cameraPos);
	_shader->setMat4Uniform("viewMatrix", camera.viewMatrix);
	_shader->setMat4Uniform("projectionMatrix", camera.projMatrix);

	// To change the coordinates into texture coordinates we need matrix to rotate YZ on 90 degrees and reflect on Y
	glm::mat3 textureMatrix = glm::mat3(glm::scale(glm::rotate(glm::mat4(), -glm::pi<float>() * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(1.0f, -1.0f, 1.0f)));
	_shader->setMat3Uniform("textureMatrix", textureMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, sampler);
	_texture->bind();
	_shader->setIntUniform("skyBoxTex", 0);

	glDepthMask(GL_FALSE); //Disabling the write to the depth buffer

	_mesh->draw();

	glDepthMask(GL_TRUE); //Enabling the write to the depth buffer

	//Disconnect sampler and shader program
	glBindSampler(0, 0);
	glUseProgram(0);
}