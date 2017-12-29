#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;

// Matrix for converting normales from the local coordinate system to camera's one
uniform mat3 normalToCameraMatrix;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexCoord;

out vec2 texCoord; // Output texture coordinates
out vec3 normalCamSpace; //normal in camera's coordinate system (CS)
out vec4 posCamSpace; //vertex coordinates in camera's CS
out vec4 lightDirCamSpace; //direction to the light

void main() {
    normalCamSpace = normalize(normalToCameraMatrix * vertexNormal); 
    
    posCamSpace = viewMatrix * modelMatrix * vec4(vertexPosition, 1.0); 
    vec4 lightPosCamSpace = viewMatrix * vec4(lightPosition, 1.0); //position of light source in camera's CS
    lightDirCamSpace = normalize(lightPosCamSpace - posCamSpace);
    texCoord = vertexTexCoord;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}
