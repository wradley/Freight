#include "GraphicsSystem.hpp"
#include "GraphicsResourceManager.hpp"
#include "Freight/FileIO.hpp"


GraphicsSystem::GraphicsSystem()
{
}


GraphicsSystem::~GraphicsSystem()
{
}


void GraphicsSystem::start(fr::EventManager &em)
{
    addOnWindowResizeEvent(em);
    addOnLoadEntityEvent(em);
    addOnLoadModelComponentEvent(em);
    addOnLoadCameraComponentEvent(em);
    addOnTransformEntitiesEvent(em);
    
    glEnable(GL_DEPTH_TEST);

    fr::String vShaderStr, fShaderStr;
    fr::LoadFileAsString("Shaders/VertexShader.glsl", vShaderStr);
    fr::LoadFileAsString("Shaders/FragmentShader.glsl", fShaderStr);
    const char *vShaderCStr = vShaderStr.c_str();
    const char *fShaderCStr = fShaderStr.c_str();
    
    GLuint vertex, fragment;
    int success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCStr, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        FR_WARN("GL Vertex Shader Compilation Error: " << infoLog);
    };

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCStr, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        FR_WARN("GL Fragment Shader Compilation Error: " << infoLog);
    };

    // shader program
    SHADERPROG = glCreateProgram();
    glAttachShader(SHADERPROG, vertex);
    glAttachShader(SHADERPROG, fragment);
    glLinkProgram(SHADERPROG);
    glGetProgramiv(SHADERPROG, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(SHADERPROG, 512, NULL, infoLog);
        FR_WARN("GL Shader Link Error: " << infoLog);
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


void GraphicsSystem::update(fr::EventManager &em)
{
    glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(SHADERPROG);
    //fr::Mat4 proj = fr::RHPerspectiveMatrix(0.1, 1000, fr::ToRad(60), (fr::Real)mWidth/(fr::Real)mHeight);
    //fr::Mat4 view = fr::RHLookAtMatrix({0, 1, 3}, {0, 0, 0}, {0, 1, 0});

    Camera camera = mEntities[mCamera].cameras.back();
    fr::Mat4 proj = fr::RHPerspectiveMatrix(camera.nearPlane, camera.farPlane, fr::ToRad(camera.fovy), (fr::Real)mWidth / (fr::Real)mHeight);
    fr::Vec3 camPos = mEntities[mCamera].transform.getMat() * camera.transform.getMat() * fr::Vec4({0,0,0,1});
    fr::Vec3 camForward = mEntities[mCamera].transform.getMat() * camera.transform.getMat() * fr::Vec4({0,0,-1,1});
    fr::Mat4 view = fr::RHLookAtMatrix(camPos, camForward, {0, 1, 0});

    for (auto [id, ent] : mEntities) 
    {
        for (auto &model : ent.models) {
            fr::Mat4 modelMat = ent.transform.getMat() * model.transform.getMat();

            glUniformMatrix4fv(glGetUniformLocation(SHADERPROG, "uProj"), 1, GL_TRUE, &proj[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(SHADERPROG, "uView"), 1, GL_TRUE, &view[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(SHADERPROG, "uModel"), 1, GL_TRUE, &modelMat[0][0]);
            glBindTexture(GL_TEXTURE_2D, model.material.textureColor);

            for (auto &mesh : model.meshes) {
                glBindVertexArray(mesh.vao);
                glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
            }
        }
    }
}


void GraphicsSystem::stop()
{
}


void GraphicsSystem::addOnWindowResizeEvent(fr::EventManager &em)
{
    em.on<WindowResizeEvent>([this](std::shared_ptr<const WindowResizeEvent> e) {
        mWidth = e->width;
        mHeight = e->height;
    });
}


void GraphicsSystem::addOnLoadEntityEvent(fr::EventManager &em)
{
    em.on<LoadEntityEvent>([this](std::shared_ptr<const LoadEntityEvent> e) {
        if (mEntities.find(e->entity) == mEntities.end()) {
            mEntities[e->entity].transform = e->transform;
        }
    });
}


void GraphicsSystem::addOnLoadModelComponentEvent(fr::EventManager &em)
{
    em.on<LoadModelComponentEvent>([this](std::shared_ptr<const LoadModelComponentEvent> e) {
        Model model;

        // meshes
        auto meshDatas = mResourceManager.loadMeshes(e->meshFp);

        for (auto &meshData : meshDatas)
        {
            Mesh mesh;
            mesh.indexCount = meshData->mIndices.size();

            glGenVertexArrays(1, &mesh.vao);
            glBindVertexArray(mesh.vao);

            glGenBuffers(1, &mesh.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * meshData->mVertices.size(), &meshData->mVertices[0], GL_STATIC_DRAW);

            glGenBuffers(1, &mesh.ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fr::u32) * meshData->mIndices.size(), &meshData->mIndices[0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
            glEnableVertexAttribArray(2);

            model.meshes.push_back(mesh);
        }

        // material
        auto imgData = mResourceManager.loadImg(e->colorFP);
        glGenTextures(1, &model.material.textureColor);
        glBindTexture(GL_TEXTURE_2D, model.material.textureColor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        GLenum format;
        switch (imgData->channelCount)
        {
        case 4:
            format = GL_RGBA;
            break;
        default:
            format = GL_RGB;
            break;
        }
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            imgData->width,
            imgData->height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            imgData->data
        );
        glGenerateMipmap(GL_TEXTURE_2D);

        model.transform = e->transform;
        model.transform.rotation = model.transform.rotation * fr::AxisAngleToQuat({1,0,0}, fr::ToRad(-90));
        mEntities[e->entity].models.push_back(model);
    });
}


void GraphicsSystem::addOnLoadCameraComponentEvent(fr::EventManager &em)
{
    em.on<LoadCameraComponentEvent>([this](std::shared_ptr<const LoadCameraComponentEvent> e) {
        Camera camera;
        camera.nearPlane = e->nearPlane;
        camera.farPlane = e->farPlane;
        camera.fovy = e->fieldOfViewY;
        camera.transform = e->transform;
        mEntities[e->entity].cameras.push_back(camera);
        mCamera = e->entity;
    });
}


void GraphicsSystem::addOnTransformEntitiesEvent(fr::EventManager &em)
{
    em.on<TransformEntitiesEvent>([this](std::shared_ptr<const TransformEntitiesEvent> e) {
        for (auto &transform : e->transforms) {
            mEntities[transform.entity].transform = transform.transform;
        }
    });
}
