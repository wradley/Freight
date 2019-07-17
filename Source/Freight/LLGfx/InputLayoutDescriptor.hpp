#pragma once
#include "Types.hpp"
#include <vector>

namespace FR8::LLGFX
{
    struct InputElementDescriptor
    {
        uint index;
        Format format;
        bool normalized;
        uint stride;
        uint offset;
    };

    struct InputLayoutDescriptor
    {
        std::vector<InputElementDescriptor> elements;
    };
}