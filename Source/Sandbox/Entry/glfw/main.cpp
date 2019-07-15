#include <glad/glad.h>
#include <glfw3.h>
#include "Freight.hpp"
#include "Math.hpp"
#include "../../Freight/LLGfx/Device.hpp"
#include "../../Freight/LLGfx/CommandQueue.hpp"
using namespace FR8;

struct Vertex
{
    Vec2 position;
    Vec4 color;
};

Vertex verts[] = {
    {{{-0.5, -0.5}}, {{1.0, 0.0, 0.0, 1.0}}},
    {{{ 0.0,  0.5}}, {{0.0, 1.0, 0.0, 1.0}}},
    {{{ 0.5, -0.5}}, {{0.0, 0.0, 1.0, 1.0}}},
};

u32 indices[] = {
    0, 1, 2
};

unsigned int vbo, vao;
unsigned int sp;

const char *vertexShaderCode = R"(
#version 460
layout (location = 0) in vec2 aPos;
void main() {
    gl_Position = vec4(aPos, 0, 1);
})";

const char *fragShaderCode = R"(
#version 460
out vec4 FragColor;
void main() {
    FragColor = vec4(1,1,1,1);
})";

#include "../../Freight/LLGfx/OpenGL/OpenGLDevice.hpp"
#include "../../Freight/LLGfx/OpenGL/OpenGLShaderCode.hpp"


LLGFX::Pipeline InitPipeline(LLGFX::Device* device)
{
    LLGFX::Shader vertexShader, fragmentShader;
    LLGFX::ShaderSignature signature;
    LLGFX::VertexLayoutDescriptor vertexLayout;

    {
        LLGFX::ShaderDescriptor vsd;
        LLGFX::OpenGLShaderCode vertexCode;
        vertexCode.code = vertexShaderCode;
        vertexShader = device->createShader(vsd);

        LLGFX::ShaderDescriptor fsd;
        LLGFX::OpenGLShaderCode fragCode;
        fragCode.code = fragShaderCode;
        fragmentShader = device->createShader(fsd);
    }

    {
        LLGFX::ShaderSignatureDescriptor d;
        d.slotCount = 0;
        signature = device->createShaderSignature(d);
    }

    {
        vertexLayout.elements.resize(2);
        vertexLayout.elements[0].index = 0;
        vertexLayout.elements[0].format = LLGFX::Format::R32G32_FLOAT;
        vertexLayout.elements[0].normalized = false;
        vertexLayout.elements[0].stride = sizeof(Vertex);
        vertexLayout.elements[0].offset = offsetof(Vertex, position);
        vertexLayout.elements[1].index = 1;
        vertexLayout.elements[1].format = LLGFX::Format::R32G32B32A32_FLOAT;
        vertexLayout.elements[1].normalized = false;
        vertexLayout.elements[1].stride = sizeof(Vertex);
        vertexLayout.elements[1].offset = offsetof(Vertex, color);
    }

    LLGFX::PipelineDescriptor d;
    d.vertexShader = d.vertexShader;
    d.fragmentShader = fragmentShader;
    d.shaderSignature = signature;
    d.vertexLayout = vertexLayout;
    d.indexFormat = LLGFX::Format::R32_UINT;
    d.primitiveTopology = LLGFX::Topology::TRIANGLE;
    return device->createPipeline(d);
}


LLGFX::Buffer InitVertexBuffer(LLGFX::Device *device)
{
    LLGFX::BufferDescriptor d;
    d.size = sizeof(verts);
    d.data = &verts;
    d.debugName = "Vertex Buffer";
    d.writeFrequency = LLGFX::BufferDescriptor::WriteFrequency::ONCE;
    d.usage = LLGFX::BufferDescriptor::Usage::CPU_WRITE_GPU_READ;
    return device->createBuffer(d);
}


LLGFX::Buffer InitIndexBuffer(LLGFX::Device* device)
{
    LLGFX::BufferDescriptor d;
    d.size = sizeof(indices);
    d.data = &indices;
    d.debugName = "Index Buffer";
    d.writeFrequency = LLGFX::BufferDescriptor::WriteFrequency::ONCE;
    d.usage = LLGFX::BufferDescriptor::Usage::CPU_WRITE_GPU_READ;
    return device->createBuffer(d);
}


void CreateBuffer()
{
    LLGFX::OpenGLDevice *device = new LLGFX::OpenGLDevice;

    LLGFX::BufferDescriptor d;
    d.data = &verts;
    d.debugName = "vertex buffer";
    d.size = sizeof(verts);
    d.usage = LLGFX::BufferDescriptor::Usage::CPU_WRITE_GPU_READ;
    d.writeFrequency = LLGFX::BufferDescriptor::WriteFrequency::ONCE;

    device->createBuffer(d);

    /*
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    */
}

void CompileShaders()
{
    unsigned int vShdr = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShdr, 1, &vertexShader, nullptr);
    glCompileShader(vShdr);

    int success;
    char infoLog[512];
    glGetShaderiv(vShdr, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShdr, 512, NULL, infoLog);
        FR8_DBG_LOG("Could not compile vertex shader\n" << infoLog);
        Logger::Flush();
    }

    unsigned int fShdr = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShdr, 1, &fragShader, nullptr);
    glCompileShader(fShdr);

    glGetShaderiv(fShdr, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShdr, 512, NULL, infoLog);
        FR8_DBG_LOG("Could not compile fragment shader\n" << infoLog);
        Logger::Flush();
    }

    sp = glCreateProgram();
    glAttachShader(sp, vShdr);
    glAttachShader(sp, fShdr);
    glLinkProgram(sp);

    glGetProgramiv(sp, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(sp, 512, NULL, infoLog);
        FR8_DBG_LOG("Could not link shader program\n" << infoLog);
        Logger::Flush();
    }

    glUseProgram(sp);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        FR8_DBG_LOG("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        FR8_DBG_LOG("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    FR8::Freight *app = FR8::Freight::GetApp();
    app->start();

    glClearColor(0, 0, 0, 1);
    CreateBuffer();
    CompileShaders();

    LLGFX::OpenGLDevice* device = new LLGFX::OpenGLDevice;
    auto cmdQueue = device->createCommandQueue();
    LLGFX::Pipeline pipeline = InitPipeline(device);
    LLGFX::Buffer vertexBuffer = InitVertexBuffer(device);
    LLGFX::Buffer indexBuffer = InitIndexBuffer(device);

    while (!glfwWindowShouldClose(window))
    {
        app->update();

        cmdQueue->clear();
        cmdQueue->setPipeline(pipeline);
        cmdQueue->setVertexBuffer(vertexBuffer);
        cmdQueue->setIndexBuffer(indexBuffer);
        cmdQueue->drawIndexed(0, 3);
        cmdQueue->commit();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app->stop();
    glfwTerminate();
    return 0;
}