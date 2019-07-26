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
        //InputLayoutDescriptor inputLayout;
        uint programPipelineObject;
        uint vertexArrayObject;
        bool valid;
    };
}