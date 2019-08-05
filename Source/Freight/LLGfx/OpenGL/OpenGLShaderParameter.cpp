#pragma once
#include "OpenGLShaderParameter.hpp"

namespace FR8::LLGFX
{
    OpenGLShaderParameter::Type OpenGLShaderConstants::getType() const
    {
        return OpenGLShaderParameter::Type::CONSTANTS;
    }
}