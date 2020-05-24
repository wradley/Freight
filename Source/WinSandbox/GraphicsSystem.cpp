#include "GraphicsSystem.hpp"
#include "GraphicsResourceManager.hpp"
#include "Freight/FileIO.hpp"
#include "Physics/PhysicsEvents.hpp"


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
    addOnLoadColliderComponentEvent(em);
    addOnTransformEntitiesEvent(em);
    addOnCollisionEvent(em);
    
    glEnable(GL_DEPTH_TEST);
    glGenVertexArrays(1, &mEmptyVAO);

    m3DShader = CreateShaderProgram("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
    mBoxColliderShader = CreateShaderProgram("Shaders/ColliderCubeVertex.glsl", "Shaders/ColliderCubeGeometry.glsl", "Shaders/ColliderCubeFragment.glsl");
    mTextShader = CreateShaderProgram("Shaders/TextVertex.glsl", "Shaders/TextGeometry.glsl", "Shaders/TextFragment.glsl");

    // sample font
    Font font;
    auto imgData = mResourceManager.loadImg("Fonts/Bits.png");
    glGenTextures(1, &font.bitmap);
    glBindTexture(GL_TEXTURE_2D, font.bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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
        GL_RGBA,
        imgData->width,
        imgData->height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        imgData->data
    );

    static const fr::Real charWidth = 7 * imgData->width / 128;
    static const fr::Real charHeight = 12 * imgData->height / 128;
    for (unsigned i = 0; i < 128; ++i) {
        fr::Real x = (i % 16) * charWidth;
        fr::Real y = std::floor(i / 16) * charHeight;
        font.charDimensions[i] = fr::Vec4{x / imgData->width, y / imgData->height, (x + charWidth) / imgData->width, (y + charHeight) / imgData->height};
    }
    mFonts.push_back(font);

    // sample text               H      e      l      l      o      ,             W      o      r      l       d       !
    const unsigned textStr[] = { 7, 0, 29, 1, 36, 2, 36, 3, 39, 4, 62, 5, 93, 6, 21, 7, 39, 8, 42, 9, 36, 10, 28, 11, 63, 12 };
    Text text;
    glCreateVertexArrays(1, &text.vao);
    glBindVertexArray(text.vao);

    glGenBuffers(1, &text.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, text.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textStr), &textStr, GL_STATIC_DRAW);

    glVertexAttribIPointer(0, 2, GL_UNSIGNED_INT, sizeof(unsigned) * 2, 0);
    glEnableVertexAttribArray(0);

    text.charCount = 13;
    text.font = 0;
    text.charWidth = 0.05;
    text.charHeight = 0.14;
    text.charPadding = 0;
    text.maxWidth = 1.0;
    text.color = {1, 0, 0};
    text.startPos = {0, 0};

    mTexts.push_back(text);

    glBindVertexArray(0);
}


void GraphicsSystem::update(fr::EventManager &em)
{
    glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m3DShader);
    //fr::Mat4 proj = fr::RHPerspectiveMatrix(0.1, 1000, fr::ToRad(60), (fr::Real)mWidth/(fr::Real)mHeight);
    //fr::Mat4 view = fr::RHLookAtMatrix({0, 1, 3}, {0, 0, 0}, {0, 1, 0});

    Camera camera = mCameras.back();
    fr::Mat4 proj = fr::RHPerspectiveMatrix(camera.nearPlane, camera.farPlane, fr::ToRad(camera.fovy), (fr::Real)mWidth / (fr::Real)mHeight);
    fr::Vec3 camPos = mEntities[camera.entity].transform.getMat() * camera.transform.getMat() * fr::Vec4({0,0,0,1});
    fr::Vec3 camForward = mEntities[camera.entity].transform.getMat() * camera.transform.getMat() * fr::Vec4({0,0,-1,1});
    fr::Mat4 view = fr::RHLookAtMatrix(camPos, camForward, {0, 1, 0});

    // models
    glUseProgram(m3DShader);
    glUniformMatrix4fv(glGetUniformLocation(m3DShader, "uProj"), 1, GL_TRUE, &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(m3DShader, "uView"), 1, GL_TRUE, &view[0][0]);

    for (auto &model : mModels) 
    {
        fr::Mat4 modelMat = getEntGlobalTform(model.entity) * model.transform.getMat();

        glUniformMatrix4fv(glGetUniformLocation(m3DShader, "uModel"), 1, GL_TRUE, &modelMat[0][0]);
        glBindTexture(GL_TEXTURE_2D, model.material.textureColor);

        for (auto &mesh : model.meshes) {
            glBindVertexArray(mesh.vao);
            glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
        }
    }

    // collider boxes
    glUseProgram(mBoxColliderShader);
    glUniformMatrix4fv(glGetUniformLocation(mBoxColliderShader, "uProj"), 1, GL_TRUE, &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(mBoxColliderShader, "uView"), 1, GL_TRUE, &view[0][0]);

    for (auto &box : mColliderBoxes)
    {
        fr::Mat4 modelMat = getEntGlobalTform(box.entity) * box.transform.getMat();
        glUniformMatrix4fv(glGetUniformLocation(mBoxColliderShader, "uModel"), 1, GL_TRUE, &modelMat[0][0]);
        glUniform3fv(glGetUniformLocation(mBoxColliderShader, "uColor"), 1, &box.color[0]);
        glBindVertexArray(mEmptyVAO);
        glDrawArrays(GL_POINTS, 0, 1);
        box.color = {0,1,0}; // reset color in case it is no longer colliding
    }

    // text
    glUseProgram(mTextShader);
    for (auto &text : mTexts)
    {
        auto &font = mFonts[text.font];
        glUniform2f(glGetUniformLocation(mTextShader, "uStartPos"), text.startPos[0], text.startPos[1]);
        glUniform2f(glGetUniformLocation(mTextShader, "uCharDimensions"), text.charWidth, text.charHeight);
        glUniform1f(glGetUniformLocation(mTextShader, "uCharPadding"), text.charPadding);
        glUniform4fv(glGetUniformLocation(mTextShader, "uBitMapLocations"), 128, (GLfloat*)font.charDimensions[0].mData);
        glBindTexture(GL_TEXTURE_2D, font.bitmap);
        glUniform3f(glGetUniformLocation(mTextShader, "uColor"), text.color[0], text.color[1], text.color[2]);
        glUniform1f(glGetUniformLocation(mTextShader, "uMaxWidth"), text.maxWidth);


        glBindVertexArray(text.vao);
        glDrawArrays(GL_POINTS, 0, text.charCount);
    }
}


void GraphicsSystem::stop()
{
}


GLuint GraphicsSystem::CreateShader(const fr::Filepath &shaderFile, GLenum type)
{
    int success;
    char infoLog[512];
    fr::String shaderStr;
    fr::LoadFileAsString(shaderFile, shaderStr);
    const char *shaderCStr = shaderStr.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCStr, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        FR_WARN("Shader compilation error [" << shaderFile << "]: " << infoLog);
    };

    return shader;
}


GLuint GraphicsSystem::CreateShaderProgram(const fr::Filepath &vPath, const fr::Filepath &fPath)
{
    int success;
    char infoLog[512];

    GLuint vertex = CreateShader(vPath, GL_VERTEX_SHADER);
    GLuint fragment = CreateShader(fPath, GL_FRAGMENT_SHADER);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vertex);
    glAttachShader(prog, fragment);
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(prog, 512, NULL, infoLog);
        FR_WARN("GL Shader Link Error: " << infoLog);
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return prog;
}


GLuint GraphicsSystem::CreateShaderProgram(const fr::Filepath &vPath, const fr::Filepath &gPath, const fr::Filepath &fPath)
{
    int success;
    char infoLog[512];

    GLuint vertex = CreateShader(vPath, GL_VERTEX_SHADER);
    GLuint geometry = CreateShader(gPath, GL_GEOMETRY_SHADER);
    GLuint fragment = CreateShader(fPath, GL_FRAGMENT_SHADER);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vertex);
    glAttachShader(prog, geometry);
    glAttachShader(prog, fragment);
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(prog, 512, NULL, infoLog);
        FR_WARN("GL Shader Link Error: " << infoLog);
    }
    glDeleteShader(vertex);
    glDeleteShader(geometry);
    glDeleteShader(fragment);

    return prog;
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
    em.on<AddEntityEvent>([this](std::shared_ptr<const AddEntityEvent> e) {
        if (mEntities.find(e->entity) == mEntities.end()) {
            mEntities[e->entity].transform = e->transform;
            mEntities[e->entity].parent = e->parent;
        }
    });
}


void GraphicsSystem::addOnLoadModelComponentEvent(fr::EventManager &em)
{
    em.on<AddModelComponentEvent>([this](std::shared_ptr<const AddModelComponentEvent> e) {
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

        model.entity = e->entity;
        model.transform = e->transform;
        mModels.push_back(model);
    });
}


void GraphicsSystem::addOnLoadCameraComponentEvent(fr::EventManager &em)
{
    em.on<AddCameraComponentEvent>([this](std::shared_ptr<const AddCameraComponentEvent> e) {
        Camera camera;
        camera.nearPlane = e->nearPlane;
        camera.farPlane = e->farPlane;
        camera.fovy = e->fieldOfViewY;
        camera.transform = e->transform;
        camera.entity = e->entity;
        mCameras.push_back(camera);
    });
}


void GraphicsSystem::addOnLoadColliderComponentEvent(fr::EventManager &em)
{
    em.on<AddColliderComponentEvent>([this](std::shared_ptr<const AddColliderComponentEvent> e) {
        if (e->type == AddColliderComponentEvent::ColliderType::BOX) {
            ColliderBox box;
            box.entity = e->entity;
            box.transform = e->offset;
            box.color = {0,1,0};
            mColliderBoxes.push_back(box);
        }
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


void GraphicsSystem::addOnCollisionEvent(fr::EventManager &em)
{
    em.on<CollisionEvent>([this](std::shared_ptr<const CollisionEvent> e) {
        for (auto &box : mColliderBoxes) {
            if (box.entity == e->a || box.entity == e->b) {
                box.color = {1, 0, 0};
            }
        }
    });
}


fr::Mat4 GraphicsSystem::getEntGlobalTform(fr::EntID id) const
{
    if (mEntities.find(id) == mEntities.end()) return fr::Mat4();
    fr::EntID parent = mEntities.at(id).parent;
    if (mEntities.at(id).parent == id) return mEntities.at(id).transform.getMat();    
    return getEntGlobalTform(parent) * mEntities.at(id).transform.getMat();
}
