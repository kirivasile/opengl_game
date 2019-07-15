#pragma once

#include "Camera.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class Application
{
public:
	Application();
	~Application();

	/**
	��������� ����������
	*/
	void start();

	/**
	������������ ������� ������ �� ���������.
	��. ��������� GLFWkeyfun ���������� GLFW
	*/
	virtual void handleKey(int key, int scancode, int action, int mods);

	/**
	������������ �������� �����
	*/
	virtual void handleMouseMove(double xpos, double ypos);

	/**
	������������ �������� ����
	*/
	virtual void handleScroll(double xoffset, double yoffset);

protected:
	/**
	�������������� ����������� ��������
	*/
	virtual void initContext();

	/**
	����������� ��������� ��������� OpenGL
	*/
	virtual void initGL();

	/**
	�������������� ����������� ��������� ������������
	*/
	virtual void initGUI();

	/**
	������� ���������� �����
	*/
	virtual void makeScene();

	/**
	��������� ���� ����������
	*/
	void run();

	/**
	��������� ���������� ����� � ����������� ������
	*/
	virtual void update();

	/**
	��������� ���������� ������������ ���������� ������������
	*/
	virtual void updateGUI();

	/**
	������������ ���� ����
	*/
	virtual void draw();

	/**
	������������ ����������� ��������� ������������
	*/
	virtual void drawGUI();

	//---------------------------------------------

	GLFWwindow* _window = nullptr; //���������� ����

	CameraInfo _camera;
	CameraMoverPtr _cameraMover;

	//����� �� ���������� �����
	double _oldTime = 0.0;
};
