#ifndef IMPORTERERR_H
#define IMPORTERERR_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"

class modelImporter
{
	const aiScene* scene;
	Assimp::Importer importer;
	std::vector<Mesh> meshes;
	std::string fileStr;
	std::string dir;

	std::vector <std::string> loadedNames;
	std::vector <Texture> loadedTex;

	void crawlNodes(aiNode* node);
	Mesh fillMesh(aiMesh* mesh);
	

public:
	modelImporter() {};
	void loadModel(const char* file);
	std::vector<Mesh> getMeshes() { return meshes; }
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type, const char* typeName);
	void clear() { meshes = {}; loadedNames = {}; loadedTex = {}; }
};

#endif // !1

