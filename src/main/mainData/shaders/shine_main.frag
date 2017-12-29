#version 330
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D originalTex;
uniform sampler2D blurTex;

void main() {
    vec4 color = texture(originalTex, texCoord);
    vec4 blurredColor = texture(blurTex, texCoord);
    fragColor = blurredColor + color;
}