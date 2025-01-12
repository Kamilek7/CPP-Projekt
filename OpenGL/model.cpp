#include "model.h"
glModel::glModel(const char* filer, modelImporter* importer)
{
	importer->loadModel(filer);
	meshes = importer->getMeshes();
	boneTransformations = importer->getBoneTransforms();
	animations = importer->getAnimations();
	time = 0;
	if (animations.size() > 0)
	{
		tree = importer->getBoneStructure();
		boneInfo = importer->getBoneInfo();
		
	}

	importer->clear();
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	linOffset = glm::vec3(0.0f, 0.0f, 0.0f);
	rotOffset = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void glModel::draw(Shader& shader, Camera& camera, float _time)
{
	this->time += _time;
	glm::mat4 modelMatrix = getMatrix();
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		if (this->animations.size() > 0 && this->animations.find(currentAnimName)!=this->animations.end())
		{
			this->boneTransformations = this->getBoneTransformations(currentAnimName);
		}

		meshes[i].Mesh::Draw(shader, camera, modelMatrix, this->boneTransformations);
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

void glModel::playAnimation(std::string name)
{
	this->currentAnimName = name;
	this->time = 0;
}

std::vector <glm::mat4> glModel::getBoneTransformations(std::string animationName)
{

	std::vector <glm::mat4> bones;
	SingleBoneTreeNode* node = this->tree.root;
	
	traverseNodeAndGetTransforms(node, glm::mat4(1.0f));
	for (int i = 0; i < boneInfo.size(); i++)
	{
		bones.push_back(boneInfo[i].transform);
	}
	node = nullptr;
	delete node;
	return bones;
}

void glModel::traverseNodeAndGetTransforms(SingleBoneTreeNode* node, glm::mat4 transform)
{
	glm::mat4 currentTransform = transform;
	glm::mat4 bonedTransformation = node->nodeTransformation;
	if (node->boneId != -1)
	{
		aiQuaternion tempRot = animations[currentAnimName].getInterpolatedRotation(time, node->boneId);
		glm::vec3 currentPos = animations[currentAnimName].getInterpolatedPosition(time, node->boneId);
		glm::vec3 currentScale = animations[currentAnimName].getInterpolatedScale(time, node->boneId);

		glm::quat currentRot;
		currentRot.w = tempRot.w;
		currentRot.x = tempRot.x;
		currentRot.y = tempRot.y;
		currentRot.z = tempRot.z;

		glm::mat4 r(1.0f);
		glm::mat4 t(1.0f);
		glm::mat4 s(1.0f);

		t = glm::translate(t, currentPos);
		r = glm::mat4_cast(currentRot);
		s = glm::scale(s, currentScale);


		bonedTransformation = t * r * s;

		currentTransform = currentTransform * bonedTransformation;

		boneInfo[node->boneId].transform = currentTransform * boneInfo[node->boneId].offset;

	}
	else
	{
		currentTransform = currentTransform * bonedTransformation;
	}

	for (int i = 0; i < node->children.size(); i++)
	{
		traverseNodeAndGetTransforms(node->children[i], currentTransform);
	}
}

