#include "import.h"

#include <iostream>

glm::mat4 aiMat4ToGLM(aiMatrix4x4& convert)
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

glm::vec3 aiVec3ToGLM(aiVector3D& vec)
{
    return glm::vec3(vec.x, vec.y, vec.z);
}

glm::quat aiQuatToGLM(aiQuaternion& quat)
{
    return glm::quat(quat.w, quat.x, quat.y, quat.z);
}


glm::mat3 aiMat3ToGLM(aiMatrix3x3& convert)
{
    glm::mat4 temp;

    temp[0][0] = convert.a1;
    temp[1][0] = convert.a2;
    temp[2][0] = convert.a3;

    temp[0][1] = convert.b1;
    temp[1][1] = convert.b2;
    temp[2][1] = convert.b3;

    temp[0][2] = convert.c1;
    temp[1][2] = convert.c2;
    temp[2][2] = convert.c3;

    return temp;
}

std::vector <Scales> modelImporter::getAnimationScales(const aiNodeAnim* animation)
{
    std::vector <Scales> scales;
    for (int i = 0; i < animation->mNumScalingKeys; i++) {

        Scales temp;
        temp.scale = aiVec3ToGLM(animation->mScalingKeys[i].mValue);

        temp.t = animation->mScalingKeys[i].mTime;
        scales.push_back(temp);
    }
    return scales;
}

std::vector <Rotations> modelImporter::getAnimationRotations(const aiNodeAnim* animation)
{
    std::vector <Rotations> scales;
    for (int i = 0; i < animation->mNumRotationKeys; i++) {

        Rotations temp;
        temp.t = animation->mRotationKeys[i].mTime;
        temp.rotation = animation->mRotationKeys[i].mValue;
        scales.push_back(temp);
    }
    return scales;
}

std::vector <Translations> modelImporter::getAnimationTranslations(const aiNodeAnim* animation)
{
    std::vector <Translations> scales;
    for (int i = 0; i < animation->mNumPositionKeys; i++) {

        Translations temp;
        temp.translation = aiVec3ToGLM(animation->mPositionKeys[i].mValue);
        temp.t = animation->mPositionKeys[i].mTime;
        scales.push_back(temp);
    }
    return scales;
}

void modelImporter::processAnimations(int id)
{
    Animation temp;
    scene->mAnimations[id];
    std::string name = scene->mAnimations[id]->mName.data;
    
    float TicksPerSecond = (float)(scene->mAnimations[id]->mTicksPerSecond != 0 ? scene->mAnimations[id]->mTicksPerSecond : 25.0f);;
    std::map <int, AnimationPacket> packetMap;
    for (int i = 0; i < (scene->mAnimations[id])->mNumChannels; i++) {

        AnimationPacket packet;

        aiNodeAnim* animation = (scene->mAnimations[id])->mChannels[i];
        int r = boneNameIndex[(scene->mAnimations[id])->mChannels[i]->mNodeName.data];
        
        packet.s = this->getAnimationScales(animation);
        packet.r = this->getAnimationRotations(animation);
        packet.t = this->getAnimationTranslations(animation);
        
        packetMap[r] = packet;
    }

    temp.passAnimationInfo(TicksPerSecond, packetMap, scene->mAnimations[id]->mDuration);
    animations[name] = temp;
}

void modelImporter::loadModel(const char* file)
{
    fileStr = std::string(file);
    dir = fileStr.substr(0, fileStr.find_last_of('/'));

    int found = -1;
    for (int i = 0; i < maxAmountOfModels; i++)
    {
        if (dir == loadedModels[i])
        {
            found = i;
            break;
        }
    }

    if (found!=-1)
    {
        this->meshes = loadedMeshes[found];
        this->animations = loadedAnimations[found];
        this->boneTransforms = loadedBoneTransforms[found];
        this->boneInfo = loadedBoneInfo[found];
        this->boneTre = loadedBoneTrees[found];
    }
    else
    {
        scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

        glm::mat4 temp(1.0f);

        crawlNodes(scene->mRootNode, temp);

        if (this->scene->mNumAnimations > 0)
        {

            for (int i = 0; i < scene->mNumAnimations; i++)
            {

                this->processAnimations(i);

            }
        }
        for (int i = 0; i < boneInfo.size(); i++)
        {
            boneTransforms.push_back(boneInfo[i].transform);
        }

        this->boneTre = BoneTree(this->scene->mRootNode, boneNameIndex);

        loadedModels[totalModels] = dir;
        loadedMeshes[totalModels] = this->meshes;
        loadedAnimations[totalModels] = this->animations;
        loadedBoneTransforms[totalModels] = this->boneTransforms;
        loadedBoneInfo[totalModels] = this->boneInfo;
        loadedBoneTrees[totalModels] = this->boneTre;
        totalModels++;
    }

}

void modelImporter::crawlNodes(aiNode* node, glm::mat4 &transform)
{
    
    
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {


        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        meshes.push_back(fillMesh(mesh));
    }
    glm::mat4 nodeTransformation = aiMat4ToGLM(node->mTransformation);
    glm::mat4 transformation = transform * nodeTransformation;
    
    if (boneNameIndex.find(node->mName.data) != boneNameIndex.end())
    {
        
        boneInfo[boneNameIndex[node->mName.data]].transform = transformation * boneInfo[boneNameIndex[node->mName.data]].offset;
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        
        crawlNodes(node->mChildren[i], transformation);
    }

}

Mesh modelImporter::fillMesh(aiMesh* mesh)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    glm::mat4 boneTransforms;

    vertToBones.resize(mesh->mNumVertices);


    if (mesh->HasBones())
    {
        for (unsigned int i = 0; i < mesh->mNumBones; i++)
        {
            int boneID = 0;
            std::string name = mesh->mBones[i]->mName.C_Str();
            if (boneNameIndex.find(name) == boneNameIndex.end())
            {
                boneID = boneNameIndex.size();
                boneNameIndex[name] = boneID;
            }
            else
            {
                boneID = boneNameIndex[name];
            }

            if (boneID == boneInfo.size())
            {
                glm::mat4 offsetTemp = aiMat4ToGLM(mesh->mBones[i]->mOffsetMatrix);
                BoneInfo temp(offsetTemp);
                boneInfo.push_back(temp);
            }

            for (int j = 0; j < mesh->mBones[i]->mNumWeights; j++)
            {
                vertToBones[mesh->mBones[i]->mWeights[j].mVertexId].addBoneData(boneID, mesh->mBones[i]->mWeights[j].mWeight);

            }

        }

    }

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 temp;

        temp.x = mesh->mVertices[i].x;
        temp.y = mesh->mVertices[i].y;
        temp.z = mesh->mVertices[i].z;
        vertex.position = temp;
        
        temp.x = mesh->mNormals[i].x;
        temp.y = mesh->mNormals[i].y;
        temp.z = mesh->mNormals[i].z;
        vertex.normal = temp;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texUV = vec;
        }
        else
            vertex.texUV = glm::vec2(0.0f, 0.0f);

        if (mesh->HasBones())
        {
            vertex.IDs.w = vertToBones[i].boneIDs[0];
            vertex.IDs.x = vertToBones[i].boneIDs[1];
            vertex.IDs.y = vertToBones[i].boneIDs[2];
            vertex.IDs.z = vertToBones[i].boneIDs[3];

            vertex.weights.w = vertToBones[i].boneWeights[0];
            vertex.weights.x = vertToBones[i].boneWeights[1];
            vertex.weights.y = vertToBones[i].boneWeights[2];
            vertex.weights.z = vertToBones[i].boneWeights[3];
        }
        else
        {
            vertex.IDs.x = -2;
        }
        

        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE, "diffuse");

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadTextures(material, aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }


    return Mesh(vertices, indices, textures);
}

std::vector<Texture> modelImporter::loadTextures(aiMaterial* mat, aiTextureType type, const char* typeName)
{
    std::vector<Texture> textures;
    int unit = 0;
    std::string tempDir = fileStr.substr(0, fileStr.find_last_of('/') + 1);

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string name = str.C_Str();
        if (name.find(":")== std::string::npos)
        {
            name = tempDir + name;
        }
        bool check = true;

        for (unsigned int j = 0; j < loadedNames.size(); j++)
        {
            if (loadedNames[j] == str.C_Str())
            {
                textures.push_back(loadedTex[j]);
                check = false;
                break;
            }
        }
        if (check)
        {   
            Texture texture(name.c_str(), typeName, unit++);
            textures.push_back(texture);
            loadedTex.push_back(texture);
            loadedNames.push_back(str.C_Str());
        }
    }
    return textures;
}