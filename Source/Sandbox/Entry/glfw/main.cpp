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
    {{-0.5, -0.5}, {1.0, 0.0, 0.0, 1.0}},
    {{ 0.0,  0.5}, {0.0, 1.0, 0.0, 1.0}},
    {{ 0.5, -0.5}, {0.0, 0.0, 1.0, 1.0}},
};

u32 indices[] = {
    0, 1, 2
};

unsigned int vbo, vao;
unsigned int sp;

const char *vertexShaderCode = R"(
#version 460
out gl_PerVertex
{
    vec4 gl_Position;
    float gl_PointSize;
};
layout (location = 0) in vec2 aPos;
void main() {
    gl_Position = vec4(aPos, 0, 1);
})";

const char *fragShaderCode = R"(
#version 460
out vec4 FragColor;
void main() {
    FragColor = vec4(0.11,0.11,0.12,1);
})";

#include "../../Freight/LLGfx/OpenGL/OpenGLDevice.hpp"
#include "../../Freight/LLGfx/OpenGL/OpenGLShader.hpp"


LLGFX::Pipeline InitPipeline(LLGFX::Device* device)
{
    LLGFX::Shader vertexShader, fragmentShader;
    LLGFX::ShaderSignature signature;
    LLGFX::InputLayoutDescriptor inputLayout;

    {
        auto vertexCode = std::make_shared<LLGFX::OpenGLShaderCode>();
        vertexCode->code = vertexShaderCode;
        LLGFX::ShaderDescriptor vsd;
        vsd.code = vertexCode;
        vsd.debugName = "Vertex Shader";
        vsd.type = LLGFX::ShaderType::VERTEX_SHADER;
        vertexShader = device->createShader(vsd);

        auto fragCode = std::make_shared<LLGFX::OpenGLShaderCode>();
        fragCode->code = fragShaderCode;
        LLGFX::ShaderDescriptor fsd;
        fsd.code = fragCode;
        fsd.debugName = "Fragment Shader";
        fsd.type = LLGFX::ShaderType::FRAGMENT_SHADER;
        fragmentShader = device->createShader(fsd);
    }

    {
        LLGFX::ShaderSignatureDescriptor d;
        d.slotCount = 0;
        signature = device->createShaderSignature(d);
    }

    {
        inputLayout.elements.resize(2);
        inputLayout.elements[0].index = 0;
        inputLayout.elements[0].format = LLGFX::Format::R32G32_FLOAT;
        inputLayout.elements[0].normalized = false;
        inputLayout.elements[0].stride = sizeof(Vertex);
        inputLayout.elements[0].offset = offsetof(Vertex, position);
        inputLayout.elements[1].index = 1;
        inputLayout.elements[1].format = LLGFX::Format::R32G32B32A32_FLOAT;
        inputLayout.elements[1].normalized = false;
        inputLayout.elements[1].stride = sizeof(Vertex);
        inputLayout.elements[1].offset = offsetof(Vertex, color);
    }

    LLGFX::PipelineDescriptor d;
    d.vertexShader = vertexShader;
    d.fragmentShader = fragmentShader;
    d.shaderSignature = signature;
    d.inputLayout = inputLayout;
    d.indexFormat = LLGFX::Format::R32_UINT;
    d.primitiveTopology = LLGFX::Topology::TRIANGLE;
    d.debugName = "pipeline";
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

    LLGFX::OpenGLDevice *device = new LLGFX::OpenGLDevice;
    auto cmdQueue = device->createCommandQueue();
    LLGFX::Pipeline pipeline = InitPipeline(device);
    LLGFX::Buffer vertexBuffer = InitVertexBuffer(device);
    LLGFX::Buffer indexBuffer = InitIndexBuffer(device);

    while (!glfwWindowShouldClose(window))
    {
        app->update();

        cmdQueue->clear({0.66, 0.55, 0.22, 1});
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