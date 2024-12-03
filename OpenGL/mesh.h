#ifndef MESH_H
#define MESH_H

#include<string>
#include "vao.h"
#include "ebo.h"
#include "camera.h"
#include "textures.h"


class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO vao;
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
	void unwrapTexCoords(glm::vec2 scale);
	void Draw(Shader& shader, Camera& camera, glm::mat4 matrix = glm::mat4(1.0f));

};
#endif