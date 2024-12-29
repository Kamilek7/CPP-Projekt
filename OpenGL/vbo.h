#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include<glad/glad.h>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
	glm::vec4 weights;
	glm::ivec4 IDs;
};

#define MAX_BONES_PER_VERT 4

struct VertexBoneData
{
	int boneIDs[MAX_BONES_PER_VERT] = { 0,0,0,0 };
	float boneWeights[MAX_BONES_PER_VERT] = { 0.0f,0.0,0.0,0.0 };

	VertexBoneData()
	{

	}

	void addBoneData(int ID, float weight)
	{
		for (int i = 0; i < MAX_BONES_PER_VERT; i++)
		{
			if (boneWeights[0] == 0.0)
			{
				boneIDs[i] = ID;
				boneWeights[i] = weight;
				break;
			}
		}
		assert(0);
	}
};

class VBO
{
public:
	GLuint buffer;
	VBO(std::vector<Vertex>& vertices);
	void bind();
	void unbind();
	void remove();
};

#endif