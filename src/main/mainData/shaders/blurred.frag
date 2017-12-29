#version 330

const int KERNEL_SIZE = 25;

float coeff[KERNEL_SIZE] = 
float[]( 0.02688, 0.029559, 0.032236, 0.034867, 0.037403, 0.039793, 0.041987, 0.043939,
0.045602, 0.04694, 0.047919, 0.048516, 0.048717, 0.048516, 0.047919, 0.04694, 0.045602, 0.043939, 0.041987,
0.039793, 0.037403, 0.034867, 0.032236, 0.029559, 0.02688 );

uniform sampler2D tex; // Texture to blur
uniform vec2 direction; // Direction of blur with radius of blur and aspect ratio, for example, (0.003, 0.0) - horizontal, (0.0, 0.002) - vertical

in vec2 vTexCoord;

out vec4 fragColor;

void main() {
    vec4 color = vec4(0.0);
    
    // Gaussian bluring
    vec2 startDir = -0.5*direction*float(KERNEL_SIZE-1); //First point of the blur
	for (int i=0; i<KERNEL_SIZE; i++) {
        // Clamp to edges all texCoords
        vec2 clampedTexCoord = vTexCoord + startDir + direction*float(i);
        clampedTexCoord.x = min(max(0., clampedTexCoord.x), 1.);
        clampedTexCoord.y = min(max(0., clampedTexCoord.y), 1.);
		color += texture2D(tex, clampedTexCoord) * coeff[i];
    }
        
    // Remove non-bright parts
    float brightness = (color.r * 0.2126) + (color.g * 0.7152) + (color.b * 0.0722);
    fragColor = color * brightness;
}