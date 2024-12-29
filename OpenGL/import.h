#ifndef IMPORTERERR_H
#define IMPORTERERR_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
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

	std::vector <std::string> loadedModels;
	std::vector <Mesh> loadedMeshes[maxAmountOfModels] = {};
	std::vector <glm::mat4> loadedBoneTransforms[maxAmountOfModels] = {};

	void crawlNodes(aiNode* node, glm::mat4& transform);
	Mesh fillMesh(aiMesh* mesh);
	

public:
	modelImporter() {};
	void loadModel(const char* file);
	std::vector<Mesh> getMeshes() { return meshes; }
	std::vector<glm::mat4> getBoneTransforms() { return boneTransforms; }
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type, const char* typeName);
	void clear() { meshes = {}; loadedNames = {}; loadedTex = {}; vertToBones = {}; boneNameIndex = {}; boneTransforms = {}; boneInfo = {}; }
};

#endif // !1

