#version 330

uniform vec3 cameraPos;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat3 textureMatrix;

layout(location = 0) in vec3 vertexPosition;

out vec3 texCoord;

void main()
{
	texCoord = textureMatrix * vertexPosition;
	
	gl_Position = projectionMatrix * viewMatrix * vec4(vertexPosition + cameraPos, 1.0);
}
