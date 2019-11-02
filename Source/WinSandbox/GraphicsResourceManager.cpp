#include "GraphicsResourceManager.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


GraphicsResourceManager::GraphicsResourceManager()
{
}


GraphicsResourceManager::~GraphicsResourceManager()
{
}


std::shared_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<fr::u32> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.position[0] = mesh->mVertices[i].x;
        vertex.position[1] = mesh->mVertices[i].y;
        vertex.position[2] = mesh->mVertices[i].z;

        vertex.normal[0] = mesh->mNormals[i].x;
        vertex.normal[1] = mesh->mNormals[i].y;
        vertex.normal[2] = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0]) 
        {
            vertex.uv[0] = mesh->mTextureCoords[0][i].x;
            vertex.uv[1] = mesh->mTextureCoords[0][i].y;
        }

        vertices.push_back(vertex);
    }
    
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return std::make_shared<Mesh>(vertices, indices);
}


void processNode(aiNode *node, const aiScene *scene, std::vector<std::shared_ptr<Mesh>> &v)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        v.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, v);
    }
}


std::vector<std::shared_ptr<Mesh>> GraphicsResourceManager::loadMeshes(const fr::Filepath &fp)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fp.absolutePath(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        FR_DEBUG_CRASH("Assimp Load Error:" << importer.GetErrorString());

    std::vector<std::shared_ptr<Mesh>> meshes;
    processNode(scene->mRootNode, scene, meshes);
    return meshes;
}


std::shared_ptr<ImgData> GraphicsResourceManager::loadImg(const fr::Filepath &fp)
{
    auto ret = std::make_shared<ImgData>();

    ret->data = stbi_load(
        fp.absolutePath().c_str(), 
        &ret->width, 
        &ret->height, 
        &ret->channelCount,
        0
    );

    return ret;
}


Mesh::Mesh(const std::vector<Vertex> &v, const std::vector<fr::u32> &i) :
    mVertices(v), mIndices(i)
{}


Mesh::~Mesh()
{
}


ImgData::ImgData() : data(nullptr), width(-1), height(-1), channelCount(-1)
{
}


ImgData::~ImgData()
{
    if (data) {
        stbi_image_free(data);
    }
}
