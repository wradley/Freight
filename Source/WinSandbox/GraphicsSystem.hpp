#pragma once
#include "Freight.hpp"
#include "GraphicsResourceManager.hpp"
#include "glad/glad.h"
#include "LoadEvents.hpp"

class GraphicsSystem
{
public:

    GraphicsSystem();
    ~GraphicsSystem();

    void start(fr::EventManager &em);
    void update(fr::EventManager &em);
    void stop();

    void addOnWindowResizeEvent(fr::EventManager &em);
    void addOnLoadEntityEvent(fr::EventManager &em);
    void addOnLoadModelComponentEvent(fr::EventManager &em);

private:

    struct Material
    {
        GLuint textureColor;
    };

    struct Mesh
    {
        GLuint vao;
        GLuint vbo;
        GLuint ebo;
        size_t indexCount;
    };

    struct Model
    {
        Material material;
        std::vector<Mesh> meshes;
        fr::Transform transform;
    };

    struct Entity
    {
        fr::Transform transform;
        std::vector<Model> models;
    };

    std::unordered_map<EntID, Entity> mEntities;

    GraphicsResourceManager mResourceManager;
    GLuint SHADERPROG;

    int mWidth;
    int mHeight;
};