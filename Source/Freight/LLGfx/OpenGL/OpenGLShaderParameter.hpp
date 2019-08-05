#pragma once
#include <vector>
#include "../Types.hpp"

namespace FR8::LLGFX
{
    struct OpenGLShaderParameter
    {
        virtual ~OpenGLShaderParameter() {}

#ifdef FR8_DBG_BUILD
        enum Type { CONSTANTS };
        virtual Type getType() const = 0;
#endif
    };

    struct OpenGLShaderConstants : public OpenGLShaderParameter
    {
        std::vector<u32> data;
        uint size;

#ifdef FR8_DBG_BUILD
        virtual Type getType() const override;
#endif
    };
}