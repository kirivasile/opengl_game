/*
Получает на вход интеполированный цвет фрагмента и копирует его на выход.
*/

#version 330

struct LightInfo 
{
    vec3 La; //ambient color
    vec3 Ld; //diffuse color
    vec3 Ls; //specular color
};
uniform LightInfo light;

struct MaterialInfo
{
    vec3 Ka; //coef of ambient reflection
    vec3 Kd; //coef of diffuse reflection
    vec3 Ks; //coef of specular reflection
};
uniform MaterialInfo material;

uniform sampler2D planetTex;

in vec2 texCoord; // Output texture coordinates
in vec3 normalCamSpace; //normal in camera's coordinate system (CS)
in vec4 posCamSpace; //vertex coordinates in camera's CS
in vec4 lightDirCamSpace; //direction to the light

const float shiness = 256.0;

out vec4 fragColor;

void main()
{
    vec3 planetColor = texture(planetTex, texCoord).rgb;
    vec3 normal = normalize(normalCamSpace); // Normalizing after the interpolation
    vec3 viewDirection = normalize(-posCamSpace.xyz); //Direction to the virtual camera
    
    float NdotL = max(dot(normal, lightDirCamSpace.xyz), 0.0);
    vec3 color = planetColor * (light.La * material.Ka + light.Ld * material.Kd * NdotL); // Color with ambient and diffuse parts
    
    if (NdotL > 0.0) 
    {
        vec3 halfVector = normalize(lightDirCamSpace.xyz + viewDirection); // Bisector between direction to the camera and to the light source
        float blinnTerm = max(dot(normal, halfVector), 0.0); // Intensity of specular light by Blinn
        blinnTerm = pow(blinnTerm, shiness); // Changing the size of speculum
        color += light.Ls * material.Ks * blinnTerm; // Adding the specular part
    }
    fragColor = vec4(color, 1.0);
}
