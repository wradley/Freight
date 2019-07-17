#pragma once
#include "../Types.hpp"
#include "../ShaderDescriptor.hpp"
#include <string>

namespace FR8::LLGFX
{
    struct OpenGLShaderCode : public ShaderCode
    {
        std::string code;
    };

    struct OpenGLShader
    {
        uint shader;
        bool valid;
    };
}