#pragma once
#include "../Defines.hpp"

#define NEW_LLGFX_HANDLE_TYPE(name)             \
struct name {                                   \
    name() : handle(0), debugName("unnamed") {} \
    ID handle;                                  \
    const char *debugName;                      \
};

namespace FR8::LLGFX
{
    typedef u32 ID;

    enum class Format
    {
        UNKNOWN,
        R32_UINT,
        R32_SINT,
        R32_FLOAT,
        R32G32_UINT,
        R32G32_SINT,
        R32G32_FLOAT,
        R32G32B32_UINT,
        R32G32B32_SINT,
        R32G32B32_FLOAT,
        R32G32B32A32_UINT,
        R32G32B32A32_SINT,
        R32G32B32A32_FLOAT,
    };

    enum class Topology
    {
        UNDEFINED,
        TRIANGLE
    };

    enum class ShaderType
    {
        VERTEX_SHADER   = 1 << 0,
        FRAGMENT_SHADER = 1 << 1,
    };

    NEW_LLGFX_HANDLE_TYPE(Pipeline);
    NEW_LLGFX_HANDLE_TYPE(Shader);
    NEW_LLGFX_HANDLE_TYPE(ShaderSignature);
    NEW_LLGFX_HANDLE_TYPE(Buffer);
    NEW_LLGFX_HANDLE_TYPE(ConstantBufferView);
    NEW_LLGFX_HANDLE_TYPE(ViewTable);
}