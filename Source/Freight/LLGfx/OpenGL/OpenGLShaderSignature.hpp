#pragma once
#include "../ShaderSignatureDescriptor.hpp"

namespace FR8::LLGFX
{
    struct OpenGLShaderSignature
    {
        ShaderSignatureDescriptor shaderSignatureDescriptor;
        bool valid;
        const char *debugName;
    };
}