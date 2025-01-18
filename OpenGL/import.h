#ifndef IMPORTERERR_H
#define IMPORTERERR_H

#include "nodeStructure.h"
#include "mesh.h"
#include "animation.h"
#include <map>

const int maxAmountOfModels = 20;

class modelImporter
{
	const aiScene* scene;
	Assimp::Importer importer;
	std::vector<Mesh> meshes;
	std::string fileStr;
	std::string dir;

	std::vector <std::string> loadedNames;
	std::vector <Texture> loadedTex;

	std::vector <VertexBoneData> vertToBones;
	std::map <std::string, int> boneNameIndex;
	std::vector <BoneInfo> boneInfo;
	std::vector <glm::mat4> boneTransforms;
	BoneTree boneTre;

	std::map <std::string,Animation> animations;

	int totalModels = 0;

	std::string loadedModels[maxAmountOfModels];
	std::vector <Mesh> loadedMeshes[maxAmountOfModels] = {};
	std::vector <glm::mat4> loadedBoneTransforms[maxAmountOfModels] = {};
	std::vector <BoneInfo> loadedBoneInfo[maxAmountOfModels] = {};
	std::map <std::string, Animation> loadedAnimations[maxAmountOfModels] = {};
	BoneTree loadedBoneTrees[maxAmountOfModels] = {};

	std::vector<Scales> getAnimationScales(const aiNodeAnim* animation);
	std::vector<Rotations> getAnimationRotations(const aiNodeAnim* animation);
	std::vector<Translations> getAnimationTranslations(const aiNodeAnim* animation);
	void processAnimations(int id);

	void crawlNodes(aiNode* node, glm::mat4& transform);
	Mesh fillMesh(aiMesh* mesh);
	

public:
	modelImporter() {};

	
	void loadModel(const char* file);

	BoneTree getBoneStructure() { return boneTre; }
	std::vector<BoneInfo> getBoneInfo() { return boneInfo; }
	std::vector<Mesh> getMeshes() { return meshes; }
	std::vector<glm::mat4> getBoneTransforms() { return boneTransforms; 
	}
	std::map <std::string,Animation> getAnimations() { return animations; }
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type, const char* typeName);

	void clear() { meshes = {}; loadedNames = {}; loadedTex = {}; vertToBones = {}; boneNameIndex = {}; boneTransforms = {}; boneInfo = {}; animations = {}; boneTre.clear(); }
};

#endif // !1