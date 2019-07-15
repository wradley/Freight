#pragma once
#include <vector>
#include "../Device.hpp"
#include "OpenGLPipeline.hpp"

namespace FR8::LLGFX
{
    class OpenGLDevice : public Device
    {
    public:

        OpenGLDevice();
        ~OpenGLDevice();

        uint getGLBufferID(Buffer b) const;
        const OpenGLPipeline* getOpenGLPipeline(Pipeline p) const;

        // overrides
        virtual std::unique_ptr<CommandQueue> createCommandQueue() override;

        virtual Buffer createBuffer(const BufferDescriptor &d) override;
        virtual void deleteBuffer(Buffer &buffer) override;
        virtual bool ownsBuffer(Buffer b) const override;

        virtual Pipeline createPipeline(const PipelineDescriptor& d) override;
        virtual void deletePipeline(Pipeline& p) override;

        virtual Shader createShader(const ShaderDescriptor& d) override;
        virtual void deleteShader(Shader& d) override;

        virtual ShaderSignature createShaderSignature(const ShaderSignatureDescriptor &d) override;
        virtual void deleteShaderSignature(ShaderSignature &s) override;

        virtual const char* getDebugName() override;

    private:

        bool hasBuffer(ID handle) const;

        // TODO: recycle deleted buffers
        std::vector<uint> mBuffers;
        std::vector<OpenGLPipeline> mPipelines;

    };
}