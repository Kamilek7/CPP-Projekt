#ifndef MESH_H
#define MESH_H



#include<string>

#include "vao.h"
#include "ebo.h"
#include "camera.h"
#include "textures.h"

#define MAX_BONES_PER_VERT 4



struct BoneInfo
{
	glm::mat4 offset;
	glm::mat4 transform;

	BoneInfo(const glm::mat4& _offset)
	{
		offset = _offset;
		transform = glm::mat4(1.0f);
	}
};

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
			if (boneWeights[i] == 0.0)
			{
				boneIDs[i] = ID;
				boneWeights[i] = weight;
				break;
			}
		}
		assert(0);
	}
};


class Mesh
{



public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO vao;
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	void unwrapTexCoords(glm::vec2 scale);
	void Draw(Shader& shader, Camera& camera, glm::mat4 matrix = glm::mat4(1.0f), std::vector <glm::mat4> boneMatrix = {glm::mat4(1.0f)});

};
#endif