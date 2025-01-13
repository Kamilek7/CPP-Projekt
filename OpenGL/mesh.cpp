#include "mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	vao.bind();

	VBO VBO(vertices);
	EBO EBO(indices);

	vao.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.linkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao.linkAttrib(VBO, 3, 4, GL_FLOAT, sizeof(Vertex), (void*)(8 * sizeof(float)));
	vao.linkAttrib(VBO, 4, 4, GL_INT, sizeof(Vertex), (void*)(12 * sizeof(float)));

	vao.unbind();
	VBO.unbind();
	EBO.unbind();
}


void Mesh::Draw(Shader& shader, Camera& camera, glm::mat4 matrix, std::vector <glm::mat4> bones)
{
	shader.on();
	vao.bind();
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].bind();
	}
	glUniform3f(glGetUniformLocation(shader.program, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.matrix(shader, "camMatrix");

	glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
	int max = bones.size();
	if (max > 50)
		max = 50;
	for (int i = 0; i <max; i++)
	{
		
		std::string name = "bones[" + std::to_string(i) + "]";
		glUniformMatrix4fv(glGetUniformLocation(shader.program, name.c_str()), 1, GL_FALSE, glm::value_ptr(bones[i]));
	}
	//if (max > 5)
	//{
	//	for (int i = 0; i < vertices.size(); i++)
	//	{
	//		for (int j = 0; j<4;j++)
	//			std::cout << vertices[i].IDs[j] << " " << vertices[i].weights[j] << std::endl;
	//	}
	//}

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
