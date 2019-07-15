#pragma once
#include "Types.hpp"
#include "VertexLayoutDescriptor.hpp"

namespace FR8::LLGFX
{
    struct PipelineDescriptor
    {
        Shader vertexShader;
        Shader fragmentShader;
        ShaderSignature shaderSignature;
        VertexLayoutDescriptor vertexLayout;
        Format indexFormat;
        Topology primitiveTopology;
    };
}