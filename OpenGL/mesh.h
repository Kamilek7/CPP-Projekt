#pragma once
#ifndef MESH_H_
#define MESH_H_



#include<string>

#include "camera.h"
#include "textures.h"
#include<glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#ifndef EBO_CLASS
#define EBO_CLASS
class EBO
{
public:
	GLuint buffer;
	EBO(std::vector<GLuint>& indices)
	{
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	}
	void unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void remove()
	{
		glDeleteBuffers(1, &buffer);
	}
};

#endif

#ifndef VBO_CLASS

#define VBO_CLASS
#define MAX_BONES_PER_VERT 4

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
	glm::vec4 weights;
	glm::ivec4 IDs;
};

struct VertexBoneData
{
	int boneIDs[MAX_BONES_PER_VERT] = { -1,-1,-1,-1 };
	float boneWeights[MAX_BONES_PER_VERT] = { 0.0f,0.0f,0.0f,0.0f };

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

class VBO
{
public:
	GLuint buffer;
	VBO(std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}
	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
	}

	void unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void remove()
	{
		glDeleteBuffers(1, &buffer);
	}
};

class VAO
{
public:
	GLuint buffer;
	VAO()
	{
		glGenVertexArrays(1, &buffer);
	}
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	{
		VBO.bind();
		if (type == GL_INT)
			glVertexAttribIPointer(layout, numComponents, type, stride, offset);
		else
			glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.unbind();
	}
	void bind()
	{
		glBindVertexArray(buffer);
	}
	void unbind()
	{
		glBindVertexArray(0);
	}
	void remove()
	{
		glDeleteVertexArrays(1, &buffer);
	}
};


#endif


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

class Mesh
{


public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO vao;
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	void Draw(Shader& shader, Camera& camera, glm::mat4 matrix = glm::mat4(1.0f), std::vector <glm::mat4> boneMatrix = {glm::mat4(1.0f)});

};

#endif