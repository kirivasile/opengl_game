#version 330

//uniform LightInfo light;
uniform vec3 lightDir;

//стандартные матрицы для преобразования координат
uniform mat4 modelMatrix; //из локальной в мировую
uniform mat4 viewMatrix; //из мировой в систему координат камеры
uniform mat4 projectionMatrix; //из системы координат камеры в усеченные координаты

//матрица для преобразования нормалей из локальной системы координат в систему координат камеры
uniform mat3 normalToCameraMatrix;

struct MaterialInfo
{
    vec3 Ka; //коэффициент отражения окружающего света
    vec3 Kd; //коэффициент отражения диффузного света
};
uniform MaterialInfo material;

layout(location = 0) in vec3 vertexPosition; //координаты вершины в локальной системе координат
layout(location = 1) in vec3 vertexNormal; //нормаль в локальной системе координат
layout(location = 2) in vec2 vertexTexCoord; //текстурные координаты
layout(location = 3) in vec2 vertexMapCoord; //текстурные координаты для карты рельефа

out vec3 normalCamSpace; // Нормаль в системе координат камеры
out vec4 posCamSpace; // Координаты вершины в системе координат камеры
out vec2 texCoord; // Текстурные координаты
out vec2 mapCoord;
out vec4 lightDirCamSpace; // Направление на источник света

void main()
{
    texCoord = vertexTexCoord;
    mapCoord = vertexMapCoord;

    posCamSpace = viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
    normalCamSpace = normalize(normalToCameraMatrix * vertexNormal); //нормаль - из локальной в систему координат камеры
    lightDirCamSpace = viewMatrix * normalize(vec4(lightDir, 0.0)); //направление на источник света - из мировой в систему координат камеры

    //float NdotL = max(dot(normalCamSpace, lightDirCamSpace.xyz), 0.0); //скалярное произведение (косинус)

    //color = light.La * material.Ka + light.Ld * material.Kd * NdotL; //цвет вершины

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}
