#pragma once
#include "Types.hpp"
#include "InputLayoutDescriptor.hpp"

namespace FR8::LLGFX
{
    struct PipelineDescriptor
    {
        Shader vertexShader;
        Shader fragmentShader;
        ShaderSignature shaderSignature;
        InputLayoutDescriptor inputLayout;
        Format indexFormat;
        Topology primitiveTopology;
        const char *debugName;
    };
}