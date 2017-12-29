#version 330

struct LightInfo
{
    vec3 La; //цвет и интенсивность окружающего света
    vec3 Ld; //цвет и интенсивность диффузного света
    vec3 Ls; //цвет и интенсивность бликового света
};
uniform LightInfo light;

uniform sampler2D snowTex;
uniform sampler2D grassTex;
uniform sampler2D sandTex;
uniform sampler2D mapTex;
uniform sampler2D specularTex;

in vec3 normalCamSpace; // Нормаль в системе координат камеры
in vec4 posCamSpace; // Координаты вершины в системе координат камеры
in vec2 texCoord; // Текстурные координаты
in vec2 mapCoord; // Координаты для карты рельефа
in vec4 lightDirCamSpace; // Направление на источник света

out vec4 fragColor; //выходной цвет фрагмента

//const vec3 Ks = vec3(1.0, 1.0, 1.0); // Коэффициент бликового отражения
const float shiness = 256.0;

void main()
{
    //vec3 diffuseColor = texture(diffuseTex, texCoord).rgb; // Возвращаем цвет текселя из текстуры
    vec3 snowColor = texture(snowTex, texCoord).rgb;
    vec3 grassColor = texture(grassTex, texCoord).rgb;
    vec3 sandColor = texture(sandTex, texCoord).rgb;
    vec3 mapColor = texture(mapTex, mapCoord).rgb;
    float Ks = texture(specularTex, mapCoord).r;
    
    vec3 diffuseColor = mapColor.r * snowColor + mapColor.g * grassColor + mapColor.b * sandColor; 
    
    vec3 normal = normalize(normalCamSpace); // Нормализуем нормаль после интерполяции
    vec3 viewDirection = normalize(-posCamSpace.xyz); // Направление на виртуальную камеру
    
    //vec3 lightDirCamSpace = normalize(light.pos - posCamSpace.xyz); // Направление на источник света
    //vec4 lightDirCamSpace = viewMatrix * normalize(vec4(light.dir, 0.0));
    float NdotL = max(dot(normal, lightDirCamSpace.xyz), 0.0); // Скалярное произведение
    
    vec3 color = diffuseColor * (light.La + light.Ld * NdotL);
    
    if (NdotL > 0.0) 
    {
      vec3 halfVector = normalize(lightDirCamSpace.xyz + viewDirection); // Биссектриса между направлением на камеру и на источник света
      float blinnTerm = max(dot(normal, halfVector), 0.0); // Интесивность бликового освещения по Блинну
      blinnTerm = pow(blinnTerm, shiness); // Регулируем размер блика
      //color += light.Ls * Ks * blinnTerm; // Добавляем бликовую часть
      color += light.Ls * vec3(Ks, Ks, Ks) * blinnTerm; // Добавляем бликовую часть
    }
    fragColor = vec4(color, 1.0);
}
