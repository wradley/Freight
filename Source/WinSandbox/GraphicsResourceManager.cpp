#include "GraphicsResourceManager.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


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

Mesh::Mesh(const std::vector<Vertex> &v, const std::vector<fr::u32> &i) :
    mVertices(v), mIndices(i)
{}

Mesh::~Mesh()
{
}
