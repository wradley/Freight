#pragma once
#include <vector>
#include <memory>
#include "Types.hpp"
#include "../Log/Log.hpp"
#include "../Math/Vector.hpp"

namespace FR8
{
    class String
    {
    public:

        virtual ~String() {}

        enum class Encoding
        {
            UTF8
        };

        virtual Encoding getEncoding() const = 0;

    private:

        void *data;
    };

    class UTF8String : public String
    {
    public:
    };
}

namespace FR8::LLGFX
{
    struct ConstantParameter
    {
        const void *src;
    };

    struct ShaderParameter
    {
        uint index;

        union {
            ConstantParameter constantParameter;
        };
    };

    struct DrawCommand
    {
        std::vector<ShaderParameter> parameters;
        
        struct VertexBufferSlot
        {
            Buffer buffer;
            uint offset;
            uint stride;
        };
        std::vector<VertexBufferSlot> vertexBufferSlots;

        Buffer indexBuffer;
        uint indexOffset;
        uint indexCount;
        Format indexFormat;
        LLGFX_DEBUG_NAME;
    };

    struct DrawCommandSet
    {
        Pipeline pipeline;
        std::vector<ShaderParameter> parameters;
        std::vector<DrawCommand> drawCommands;
        LLGFX_DEBUG_NAME;
    };

    class CommandQueue
    {
    public:

        virtual ~CommandQueue() {}

        //virtual void copy(Buffer src, u32 srcOffset, Buffer dst, u32 dstOffset, u32 size) = 0;

        // drawing
        /*virtual void setPipeline(Pipeline p) = 0;
        virtual void setShaderConstant(uint signatureParameterIndex, const void *srcData, uint srcSize, uint dst32BitOffset) = 0;
        virtual void setShaderConstantBufferView(uint signatureIndex, ConstantBufferView c) = 0;
        virtual void setShaderViewTable(uint signatureIndex, ViewTable c) = 0;
        virtual void setVertexBuffer(Buffer b) = 0;
        virtual void setIndexBuffer(Buffer b) = 0;
        virtual void drawIndexed(u32 offset, u32 count) = 0;*/

        virtual void pushDebugStr(const std::string &s) = 0;
        virtual void popDebugStr() = 0;

        virtual void clear(const Flt4 &color) = 0;
        virtual void submit(const DrawCommandSet &set) = 0;
        virtual void commit() = 0;
    };
}