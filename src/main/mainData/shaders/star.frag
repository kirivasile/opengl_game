/*
Получает на вход интеполированный цвет фрагмента и копирует его на выход.
*/

#version 330

uniform sampler2D starTex;

in vec2 texCoord;

out vec4 fragColor;

void main()
{
    vec3 starColor = texture(starTex, texCoord).rgb;
    fragColor = vec4(2.0 * pow(starColor.r, 0.5), 2.0 * pow(starColor.g, 0.5), 2.0 * pow(starColor.b, 0.5), 1.0);
}
