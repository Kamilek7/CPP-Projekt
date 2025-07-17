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
uniform mat4 bones[50];
uniform vec3 playerPos;

void main()
{

		if (IDs[0]!=-2)
		{
			mat4 bone = bones[IDs[0]]*weights[0];
			bone += bones[IDs[1]]*weights[1];
			bone += bones[IDs[2]]*weights[2];
			bone += bones[IDs[3]]*weights[3];
			crntPos = vec3(model * (bone*vec4(aPos, 1.0f)));
		}
		else
		{
			crntPos = vec3(model * vec4(aPos, 1.0f));
		}
		mat3 normalMatrix = mat3(model);
		normalMatrix = inverse(normalMatrix);
		normalMatrix = transpose(normalMatrix);
		Normal = normalize(aNormal*normalMatrix);
		texCoord = aTex;
		IDsPass = IDs;
		weightsPass = weights;
		gl_Position = camMatrix * vec4(crntPos, 1.0);

}