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

private:

    static GLuint CreateShader(const fr::Filepath &shaderFile, GLenum type);
    static GLuint CreateShaderProgram(const fr::Filepath &vertex, const fr::Filepath &fragment);
    static GLuint CreateShaderProgram(const fr::Filepath &vertex, const fr::Filepath &geometry, const fr::Filepath &fragment);

    void addOnWindowResizeEvent(fr::EventManager &em);
    void addOnLoadEntityEvent(fr::EventManager &em);
    void addOnLoadModelComponentEvent(fr::EventManager &em);
    void addOnLoadCameraComponentEvent(fr::EventManager &em);
    void addOnLoadColliderComponentEvent(fr::EventManager &em);
    void addOnTransformEntitiesEvent(fr::EventManager &em);

    fr::Mat4 getEntGlobalTform(EntID id) const;

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
        EntID entity;
        Material material;
        std::vector<Mesh> meshes;
        fr::Transform transform;
    };

    struct Camera
    {
        EntID entity;
        fr::Transform transform;
        fr::Real nearPlane;
        fr::Real farPlane;
        fr::Real fovy;
    };

    struct Entity
    {
        EntID parent;
        fr::Transform transform;
    };

    struct ColliderBox
    {
        EntID entity;
        fr::Transform transform;
    };

    GLuint mEmptyVAO;
    std::unordered_map<EntID, Entity> mEntities;
    std::vector<Model> mModels;
    std::vector<Camera> mCameras;
    std::vector<ColliderBox> mColliderBoxes;

    GraphicsResourceManager mResourceManager;
    GLuint m3DShader, mBoxColliderShader;

    int mWidth;
    int mHeight;
};