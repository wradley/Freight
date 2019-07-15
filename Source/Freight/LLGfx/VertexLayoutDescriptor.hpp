#pragma once
#include "Types.hpp"
#include <vector>

namespace FR8::LLGFX
{
    struct VertexElementDescriptor
    {
        uint index;
        Format format;
        bool normalized;
        uint stride;
        uint offset;
    };

    struct VertexLayoutDescriptor
    {
        std::vector<VertexElementDescriptor> elements;
    };
}