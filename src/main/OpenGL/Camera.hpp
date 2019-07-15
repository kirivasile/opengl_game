#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

struct CameraInfo
{
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
};

/**
����� ��� ���������� ����������� �������
*/
class CameraMover
{
public:
	CameraMover() {}
	virtual ~CameraMover() {}

	/**
	���������� ��������� ����������� ������ � ���� 2� ������: ������� ���� � ��������
	*/
	CameraInfo cameraInfo() const { return _camera; }

	/**
	������������ ������� ������ �� ���������.
	��. ��������� GLFWkeyfun ���������� GLFW
	*/
	virtual void handleKey(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

	/**
	������������ �������� �����
	*/
	virtual void handleMouseMove(GLFWwindow* window, double xpos, double ypos) = 0;

	/**
	������������ �������� ����
	*/
	virtual void handleScroll(GLFWwindow* window, double xoffset, double yoffset) = 0;

	/**
	��������� ��������� ����������� ������
	*/
	virtual void update(GLFWwindow* window, double dt) = 0;

protected:
	CameraInfo _camera;
};

using CameraMoverPtr = std::shared_ptr<CameraMover>;

/**
��������� ������ �������� � ����������� �����������. ������ ������ ������� � ����� �����.
*/
class OrbitCameraMover : public CameraMover
{
public:
	void handleKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	void handleMouseMove(GLFWwindow* window, double xpos, double ypos) override;
	void handleScroll(GLFWwindow* window, double xoffset, double yoffset) override;
	void update(GLFWwindow* window, double dt) override;

protected:
	//��������� ����������� ������ �������� � ����������� ���������
	double _phiAng = 0.0;
	double _thetaAng = 0.0;
	double _r = 5.0;

	//��������� ������� ���� �� ���������� �����
	double _oldXPos = 0.0;
	double _oldYPos = 0.0;
};

/**
������ ������ ����� ������
*/
class FreeCameraMover : public CameraMover
{
public:
	FreeCameraMover();

	void handleKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	void handleMouseMove(GLFWwindow* window, double xpos, double ypos) override;
	void handleScroll(GLFWwindow* window, double xoffset, double yoffset) override;
	void update(GLFWwindow* window, double dt) override;

protected:
	//��������� ����������� ������ �������� � ����������� ���������
	glm::vec3 _pos;
	glm::quat _rot;

	//��������� ������� ���� �� ���������� �����
	double _oldXPos = 0.0;
	double _oldYPos = 0.0;
};

