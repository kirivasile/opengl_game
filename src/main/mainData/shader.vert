/*
Преобразует координаты вершины из локальной системы координат в Clip Space.
Копирует цвет вершины из вершинного атрибута в выходную переменную color.
*/

#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;

out vec4 color;

void main()
{
	color = vec4(1.0, 1.0, 0.0, 1.0);
	color.r = color.r + vertexPosition.z * 2;
	color.g = color.g - vertexPosition.z * 2;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}
