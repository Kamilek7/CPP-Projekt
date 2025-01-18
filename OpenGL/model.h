#ifndef MODEL_H
#define MODEL_H

#include "import.h"


class glModel
{

	std::vector<glm::mat4> getBoneTransformations(std::string animationName);

	void traverseNodeAndGetTransforms(SingleBoneTreeNode* node, glm::mat4 transform);


	BoneTree tree;
	std::vector <BoneInfo> boneInfo;
	
	std::vector<glm::mat4> boneTransformations;

public:
	std::map <std::string, Animation> animations;
	glModel() {};
	glModel(const char* filer, modelImporter* importer);
	void draw(Shader& shader, Camera& camera, float _time);
	glm::mat4 getMatrix();

	void playAnimation(std::string name);

	std::string currentAnimName;
	float time;

	std::vector<Mesh> meshes;

	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;
	glm::vec3 linOffset;
	glm::quat rotOffset;

};
#endif