#version 330

uniform sampler2D starTex;
uniform float time;

in vec2 texCoord;

out vec4 fragColor;

void main()
{
    //vec3 starColor = texture(starTex, texCoord).rgb;
    vec3 starColor = vec3(1.0);
    fragColor = vec4(starColor, 1.0);
}
