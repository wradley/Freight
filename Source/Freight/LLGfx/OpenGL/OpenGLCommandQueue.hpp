#pragma once
#include <memory>
#include <vector>
#include "../CommandQueue.hpp"
#include "OpenGLPipeline.hpp"

namespace FR8::LLGFX
{
    class OpenGLDevice;

    class OpenGLCommandQueue : public CommandQueue
    {
    public:

        OpenGLCommandQueue(OpenGLDevice* device);
        ~OpenGLCommandQueue();

        virtual void setPipeline(Pipeline p) override;
        virtual void setShaderConstant(uint index, i32 src, u32 dstOffset) override;
        virtual void setShaderConstantBufferView(uint index, ConstantBufferView c) override;
        virtual void setShaderViewTable(uint index, ViewTable c) override;
        virtual void setVertexBuffer(Buffer b) override;
        virtual void setIndexBuffer(Buffer b) override;
        virtual void drawIndexed(u32 offset, u32 count) override;
        virtual void clear(const Flt4 &color) override;
        virtual void commit() override;
        virtual void reset() override;

    private:

        //uint getGLVAO(uint glVertexBuffer, uint glIndexBuffer);

        OpenGLDevice *mDevice;
        OpenGLPipeline mBoundPipeline;
        uint mVAO;
        //std::vector<std::vector<uint>> mVAOs;

    };
}