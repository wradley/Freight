#pragma once
#include <vector>
#include <memory>
#include "Types.hpp"
#include "../Log/Log.hpp"

namespace FR8::LLGFX
{
    class CommandQueue
    {
    public:

        virtual ~CommandQueue() {}

        //virtual void copy(Buffer src, u32 srcOffset, Buffer dst, u32 dstOffset, u32 size) = 0;

        // drawing
        virtual void setPipeline(Pipeline p) = 0;
        virtual void setShaderConstant(uint index, i32 src, u32 dstOffset) = 0;
        virtual void setShaderConstantBufferView(uint index, ConstantBufferView c) = 0;
        virtual void setShaderViewTable(uint index, ViewTable c) = 0;
        virtual void setVertexBuffer(Buffer b) = 0;
        virtual void setIndexBuffer(Buffer b) = 0;
        virtual void drawIndexed(u32 offset, u32 count) = 0;

        virtual void clear() = 0;
        virtual void commit() = 0;
        virtual void reset() = 0;
    };
}