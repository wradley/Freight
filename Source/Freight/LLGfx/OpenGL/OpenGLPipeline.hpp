#pragma once
#include "../Types.hpp"

namespace FR8::LLGFX
{
    struct OpenGLPipeline
    {
        Topology primitiveTopology;
        Format indexType;
    };
}