#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec2 texCoord;
in vec4 weightsPass;
flat in ivec4 IDsPass;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec2 texScaler;
uniform vec3 camPos;

struct PointLight {    
    vec3 position;
    vec4 lightColor;
};  

uniform PointLight pointLights[NR_LIGHTS];

vec4 calcPointLight(PointLight light, vec2 TexCoord)
{
	vec4 result = vec4(0.0f);

	vec3 lightVec = light.position - crntPos;
	float dist = length(lightVec);
	if (dist<10.0)
	{
		float a = 0.5;
		float b = 0.7;
		float c = 1.0;
		float inten = 1.0f / (a * dist * dist + b * dist + c);

		vec3 normal = normalize(Normal);
		vec3 lightDirection = normalize(lightVec);
		float diffuse = max(dot(normal, lightDirection), 0.0f);
		float specularLight = 0.40f;

		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 reflectionDirection = reflect(-lightDirection, normal);
		float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
		float specular = specAmount * specularLight;
		result = (texture(diffuse0, TexCoord) * (diffuse * inten) + texture(specular0, TexCoord).r * specular * inten) * light.lightColor;
	}
	return result;

} 

void main()
{
	vec2 TexCoord;
	if (texScaler[0]!=0 && texScaler[1]!=0)
	{
		TexCoord[0] = texCoord[1]*texScaler[1];
		TexCoord[1] = texCoord[0]*texScaler[0];
	}
	else
	{
			TexCoord[0] = texCoord[0];
			TexCoord[1] = texCoord[1];
	}
	vec4 result;

	for(int i = 0; i < NR_LIGHTS; i++)
        result += calcPointLight(pointLights[i], TexCoord);
	result += texture(diffuse0, TexCoord)*0.2f;


	FragColor = result;

}