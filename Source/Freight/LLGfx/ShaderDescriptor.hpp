#pragma once
#include "Types.hpp"
#include <memory>

namespace FR8::LLGFX
{
    struct ShaderCode
    {
        virtual ~ShaderCode() = 0;
    };

    ShaderCode::~ShaderCode() {}


    struct ShaderDescriptor
    {
        ShaderType type;
        std::shared_ptr<const ShaderCode> code;
    };
}