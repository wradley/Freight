#pragma once
#include <string>
#include "../Defines.hpp"


#ifdef FR8_DEBUG_BUILD
#define LLGFX_DEBUG_NAME std::string debugName
#define LLGFX_SET_DEBUG_NAME(item, name) item.debugName = name
#define LLGFX_GET_DEBUG_NAME(item) item.debugName
#define LLGFX_NEW_HANDLE_TYPE(name)             \
struct name {                                   \
    name() : handle(0), debugName("UNNAMED") {}\
    ID handle;                                  \
    LLGFX_DEBUG_NAME;                           \
};
#else
#define LLGFX_DEBUG_NAME
#define SET_LLGFX_DEBUG_NAME(item, name)
#define LLGFX_GET_DEBUG_NAME(item) "_"
#define LLGFX_NEW_HANDLE_TYPE(name)             \
struct name {                                   \
    name() : handle(0) {}                       \
    ID handle;                                  \
};
#endif



namespace FR8::LLGFX
{
    typedef u32 ID;

    enum class Format
    {
        NIL,
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
        NIL,
        UNDEFINED,
        TRIANGLE
    };

    enum class ShaderType
    {
        NIL = 0,
        VERTEX_SHADER,
        FRAGMENT_SHADER,
    };

    typedef uint ShaderTypeBit;

    LLGFX_NEW_HANDLE_TYPE(Pipeline);
    LLGFX_NEW_HANDLE_TYPE(Shader);
    LLGFX_NEW_HANDLE_TYPE(ShaderSignature);
    LLGFX_NEW_HANDLE_TYPE(Buffer);
    LLGFX_NEW_HANDLE_TYPE(ConstantBufferView);
    LLGFX_NEW_HANDLE_TYPE(ViewTable);
}

namespace FR8
{
    const LLGFX::ShaderTypeBit LLGFX_NIL_SHADER_BIT         = 0;
    const LLGFX::ShaderTypeBit LLGFX_VERTEX_SHADER_BIT      = 1 << 0;
    const LLGFX::ShaderTypeBit LLGFX_FRAGMENT_SHADER_BIT    = 1 << 1;
}