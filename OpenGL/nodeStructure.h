#ifndef BONE_NODE_STRUCTURE_H_

#define BONE_NODE_STRUCTURE_H_
#include <glm/glm.hpp>
#include <vector>
#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



class SingleBoneTreeNode
{
public:
	int boneId;
	glm::mat4 nodeTransformation;
	SingleBoneTreeNode* parent;
	std::vector <SingleBoneTreeNode*> children;
	SingleBoneTreeNode()
	{
	}



	void makeParentChildConnection(SingleBoneTreeNode* parent)
	{
		this->parent = parent;
		parent->children.push_back(this);
	}
};

class BoneTree
{
	std::map <std::string, int> BoneNameMap;

	glm::mat4 aiMat4ToGLM2(aiMatrix4x4& convert)
	{
		glm::mat4 temp;

		temp[0][0] = convert.a1;
		temp[1][0] = convert.a2;
		temp[2][0] = convert.a3;
		temp[3][0] = convert.a4;

		temp[0][1] = convert.b1;
		temp[1][1] = convert.b2;
		temp[2][1] = convert.b3;
		temp[3][1] = convert.b4;

		temp[0][2] = convert.c1;
		temp[1][2] = convert.c2;
		temp[2][2] = convert.c3;
		temp[3][2] = convert.c4;

		temp[0][3] = convert.d1;
		temp[1][3] = convert.d2;
		temp[2][3] = convert.d3;
		temp[3][3] = convert.d4;

		return temp;
	}

public:
	SingleBoneTreeNode* root;
	BoneTree() {};
	BoneTree(aiNode* rootNode, std::map <std::string, int>& BoneNameMap)
	{
		this->root = new SingleBoneTreeNode();
		this->BoneNameMap = BoneNameMap;
		processAiNode(rootNode, root);
	}
	void processAiNode(aiNode* node, SingleBoneTreeNode* current)
	{
		current->nodeTransformation = aiMat4ToGLM2(node->mTransformation);
		if (BoneNameMap.find(node->mName.data) != BoneNameMap.end())
			current->boneId = BoneNameMap[node->mName.data];
		else
			current->boneId = -1;
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			SingleBoneTreeNode* temp = new SingleBoneTreeNode();
			temp->makeParentChildConnection(current);
			processAiNode(node->mChildren[i], temp);
		}
	}
	void clear()
	{
		this->root = nullptr;

		// Reszta pozniej
	}
};


#endif