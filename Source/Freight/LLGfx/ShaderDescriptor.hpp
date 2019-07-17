#pragma once
#include "Types.hpp"
#include <memory>

namespace FR8::LLGFX
{
    struct ShaderCode
    {
        inline virtual ~ShaderCode() {}
    };


    struct ShaderDescriptor
    {
        ShaderType type;
        const char *debugName;
        std::shared_ptr<const ShaderCode> code;
    };
}