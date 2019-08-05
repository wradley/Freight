#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../CommandQueue.hpp"
#include "../ShaderSignatureDescriptor.hpp"
#include "OpenGLPipeline.hpp"
#include "OpenGLShaderParameter.hpp"

namespace FR8::LLGFX
{
    class OpenGLDevice;

    class OpenGLCommandQueue : public CommandQueue
    {
    public:

        OpenGLCommandQueue(OpenGLDevice* device);
        ~OpenGLCommandQueue();

        /*virtual void setPipeline(Pipeline p) override;
        virtual void setShaderConstant(uint signatureParameterIndex, const void *srcData, uint srcSize, uint dst32BitOffset) override;
        virtual void setShaderConstantBufferView(uint signatureIndex, ConstantBufferView c) override;
        virtual void setShaderViewTable(uint signatureIndex, ViewTable c) override;
        virtual void setVertexBuffer(Buffer b) override;
        virtual void setIndexBuffer(Buffer b) override;
        virtual void drawIndexed(u32 offset, u32 count) override;*/

        virtual void clear(const Flt4 &color) override;
        virtual void submit(const DrawCommandSet &set) override;
        virtual void commit() override;

    private:

        void setShaderParameters(const ShaderSignatureDescriptor &signature, const std::vector<ShaderParameter> &parameters);
        void setShaderConstant(const SignatureParameterDescriptor &descriptor, const void *src);

    private:

        std::vector<std::unique_ptr<OpenGLShaderParameter>> mShaderParameters;

        OpenGLDevice *mDevice;

        OpenGLPipeline mBoundPipeline;
        bool mPipelineHasChanged;
    };
}