#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 centerPosition;
uniform float time;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexCoord;

out vec2 texCoord; // Output texture coordinates
out vec3 coronaOffset;

void main() {
    mat4 modelView = viewMatrix * modelMatrix;
    
    modelView[0][0] = 1.0; 
    modelView[0][1] = 0.0; 
    modelView[0][2] = 0.0; 
    modelView[1][0] = 0.0; 
    modelView[1][1] = 1.0; 
    modelView[1][2] = 0.0; 
    modelView[2][0] = 0.0; 
    modelView[2][1] = 0.0; 
    modelView[2][2] = 1.0;
    
    gl_Position = projectionMatrix * modelView * vec4(vertexPosition, 1.0);
    texCoord = vertexTexCoord;
    
    vec4 modelVertexPosition = modelMatrix * vec4(vertexPosition, 1.0);
    // Vector from the center of star to the vertex in corona
    coronaOffset = modelVertexPosition.xyz - centerPosition;
}