#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec4 weights;
layout (location = 4) in ivec4 IDs;

out vec3 crntPos;
out vec3 Normal;
out vec2 texCoord;
out vec4 weightsPass;
flat out ivec4 IDsPass;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));
	mat3 normalMatrix = mat3(model);
	normalMatrix = inverse(normalMatrix);
	normalMatrix = transpose(normalMatrix);
	Normal = normalize(aNormal*normalMatrix);
	texCoord = aTex;
	IDsPass = IDs;
	weightsPass = weights;
	gl_Position = camMatrix * vec4(crntPos, 1.0);

}