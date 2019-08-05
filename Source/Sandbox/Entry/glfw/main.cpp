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

const uint VERTEX_SIZE = sizeof(Vertex);

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
};
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (binding = 0, std140) uniform MainBlock {
    mat2 uRot;
}

void main() {
    vec2 pos = uRot * aPos;
    gl_Position = vec4(pos.x, pos.y, 0, 1);
})";

const char *fragShaderCode = R"(
#version 460
layout (location=0) uniform float uStrength;
layout (location=0) out vec4 oFragColor;
void main() {
    float strength = (uStrength + 1.0) / 2.0;
    vec3 color = vec3(0.38, 0.82, 0.49) * strength;
    oFragColor = vec4(color,1);
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
        LLGFX_SET_DEBUG_NAME(vsd, "Vertex Shader");
        vsd.type = LLGFX::ShaderType::VERTEX_SHADER;
        vertexShader = device->createShader(vsd);

        auto fragCode = std::make_shared<LLGFX::OpenGLShaderCode>();
        fragCode->code = fragShaderCode;
        LLGFX::ShaderDescriptor fsd;
        fsd.code = fragCode;
        LLGFX_SET_DEBUG_NAME(fsd, "Fragment Shader");
        fsd.type = LLGFX::ShaderType::FRAGMENT_SHADER;
        fragmentShader = device->createShader(fsd);
    }

    {
        LLGFX::SignatureParameterDescriptor constant;
        constant.parameterType = LLGFX::SignatureParameterDescriptor::ParameterType::CONSTANT;
        constant.access = LLGFX_VERTEX_SHADER_BIT | LLGFX_FRAGMENT_SHADER_BIT;
        constant.constantDescriptor.rowFormat = LLGFX::Format::R32_FLOAT;
        constant.constantDescriptor.shaderRegister = 0;

        LLGFX::ShaderSignatureDescriptor d;
        d.parameters.push_back(constant);

        signature = device->createShaderSignaure(d);
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
        FR8_DEBUG_LOG("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        FR8_DEBUG_LOG("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    FR8::Freight *app = FR8::Freight::GetApp();
    app->start();

    LLGFX::OpenGLDevice *device = new LLGFX::OpenGLDevice;
    auto cmdQueue = device->createCommandQueue();
    LLGFX::Pipeline pipeline = InitPipeline(device);
    LLGFX::Buffer vertexBuffer = InitVertexBuffer(device);
    LLGFX::Buffer indexBuffer = InitIndexBuffer(device);

    float dx = 0.0f;
    float dxSin = dx;
    while (!glfwWindowShouldClose(window))
    {
        dxSin = sin(dx);
        dx += 0.05f;
        app->update();

        cmdQueue->clear({0.11, 0.14, 0.22, 1});

        LLGFX::DrawCommandSet ds;
        ds.pipeline = pipeline;
        ds.drawCommands.resize(1);
        LLGFX_SET_DEBUG_NAME(ds, "Draw Command Set");
        ds.drawCommands[0].parameters.resize(1);
        ds.drawCommands[0].parameters[0].index = 0;
        ds.drawCommands[0].parameters[0].constantParameter.src = &dx;
        ds.drawCommands[0].vertexBufferSlots.resize(1);
        ds.drawCommands[0].vertexBufferSlots[0].buffer = vertexBuffer;
        ds.drawCommands[0].vertexBufferSlots[0].offset = 0;
        ds.drawCommands[0].vertexBufferSlots[0].stride = 0; // MAYBE: sizeof(VERTEX)
        ds.drawCommands[0].indexBuffer = indexBuffer;
        ds.drawCommands[0].indexOffset = 0;
        ds.drawCommands[0].indexCount = 3;
        ds.drawCommands[0].indexFormat = LLGFX::Format::R32_UINT;
        LLGFX_SET_DEBUG_NAME(ds.drawCommands[0], "Draw Command");
        
        cmdQueue->submit(ds);
        cmdQueue->commit();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app->stop();
    glfwTerminate();
    return 0;
}