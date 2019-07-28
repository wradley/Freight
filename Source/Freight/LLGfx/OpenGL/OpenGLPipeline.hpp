#pragma once
#include <glad/glad.h>
#include "../Types.hpp"
#include "../InputLayoutDescriptor.hpp"

namespace FR8::LLGFX
{
    struct OpenGLPipeline
    {
        GLenum primitiveTopology;
        GLenum indexType;
        uint programPipelineObject;
        Shader vertexShaderProgram;
        Shader fragmentShaderProgram;
        ShaderSignature shaderSignature;
        uint vertexArrayObject;
        bool valid;
        const char *debugName;
    };
}