#include "GraphicsSystem.hpp"
#include "LoadEvents.hpp"
#include "GraphicsResourceManager.hpp"
#include "Freight/FileIO.hpp"


const float PTPOS = 0.3f;

Vertex vertices[] = {
    {{-PTPOS,-PTPOS,0}},
    {{ PTPOS,-PTPOS,0}},
    {{-PTPOS, PTPOS,0}},
    {{ PTPOS, PTPOS,0}},
};

fr::u32 indices[] = {
    0, 2, 3,
    3, 1, 0
};


GraphicsSystem::GraphicsSystem()
{
}


GraphicsSystem::~GraphicsSystem()
{
}


void GraphicsSystem::start(std::shared_ptr<fr::EventManager> em)
{
    glEnable(GL_DEPTH_TEST);

    em->on<LoadEntityEvent>([](std::shared_ptr<const LoadEntityEvent> e) {
        FR_LOG("Graphics System Loading Entity: " << e->entity);
    });

    em->on<LoadModelComponentEvent>([](std::shared_ptr<const LoadModelComponentEvent> e) {
        FR_LOG("Graphics System Loading Model Component for: " << e->entity);
    });

    fr::Filepath fp("Meshes/Fence1.fbx");
    std::vector<std::shared_ptr<Mesh>> meshes = mResourceManager.loadMeshes(fp);
    Mesh &mesh = *meshes[0];
    NUM_INDICES = mesh.mIndices.size();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.mVertices.size(), &mesh.mVertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fr::u32) * mesh.mIndices.size(), &mesh.mIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);

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

    // color texture
    auto imgData = mResourceManager.loadImg("Textures/FenceColor.png");
    glGenTextures(1, &COLOR);
    glBindTexture(GL_TEXTURE_2D, COLOR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGB, 
        imgData->width, 
        imgData->height, 
        0,
        GL_RGB, 
        GL_UNSIGNED_BYTE, 
        imgData->data
    );
    glGenerateMipmap(GL_TEXTURE_2D);
}


void GraphicsSystem::update(std::shared_ptr<fr::EventManager> em)
{
    glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(SHADERPROG);
    fr::Mat4 proj = fr::RHProjectionMatrix(0.1, 1000, fr::ToRad(60), (fr::Real)800/(fr::Real)600);
    static float height = 0;
    float newheight = sin(height) * 5;
    height += 0.05f;
    //fr::Mat4 view = fr::RHLookAtMatrix({0, 0, 5}, {0, 0, 0}, {0, 1, 0});
    fr::Mat4 view = fr::Translate({0,0,3});
    static int deg = 0;
    fr::Quat modelRot = fr::AxisAngleToQuat({1,0,0}, fr::ToRad(deg++));// *fr::AxisAngleToQuat({1,0,0}, fr::ToRad(-90));
    fr::Mat4 model = fr::ToMat4(modelRot.getNormalized());

    glUniformMatrix4fv(glGetUniformLocation(SHADERPROG, "uProj"), 1, GL_TRUE, &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(SHADERPROG, "uView"), 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(SHADERPROG, "uModel"), 1, GL_TRUE, &model[0][0]);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, 0);
}


void GraphicsSystem::stop()
{
}
