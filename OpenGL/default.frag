#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec3 camPos;

struct PointLight {    
    vec3 position;
    vec4 lightColor;
};  

uniform PointLight pointLights[NR_LIGHTS];

vec4 calcPointLight(PointLight light)
{
	vec3 lightVec = light.position - crntPos;
	float dist = length(lightVec);
	float a = 0.5;
	float b = 0.7;
    float c = 1.0;
	float inten = 1.0f / (a * dist * dist + b * dist + c);

	float ambient = 0.15f;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float specularLight = 0.40f;

	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * light.lightColor;

} 

void main()
{
	vec4 result;
    for(int i = 0; i < NR_LIGHTS; i++)
        result += calcPointLight(pointLights[i]);
	FragColor = result;

}