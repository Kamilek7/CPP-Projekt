#include "model.h"

glModel::glModel(const char* filer, modelImporter* importer)
{
	importer->loadModel(filer);
	meshes = importer->getMeshes();
	importer->clear();
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	linOffset = glm::vec3(0.0f, 0.0f, 0.0f);
	rotOffset = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void glModel::draw(Shader& shader, Camera& camera)
{
	glm::mat4 modelMatrix = getMatrix();
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Mesh::Draw(shader, camera, modelMatrix);
	}
}

glm::mat4 glModel::getMatrix()
{
	glm::vec3 trans = this->translation;
	glm::mat4 t = glm::mat4(1.0f);
	trans += linOffset;

	glm::mat4 r = glm::mat4(1.0f);
	glm::mat4 s = glm::mat4(1.0f);

	t = glm::translate(t, trans);
	r = glm::mat4_cast(this->rotation);
	s = glm::scale(s, this->scale);

	return t * r * s;
}