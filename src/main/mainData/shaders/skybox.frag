#version 330

uniform samplerCube skyBoxTex;

in vec3 texCoord; // texture coordinates (interpolated between the vertices of the triangle)

out vec4 fragColor; //output color of the fragment

void main()
{
	vec3 texColor = texture(skyBoxTex, texCoord).rgb;

	fragColor = vec4(texColor, 1.0);
}
