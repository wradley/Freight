#pragma once
#include <vector>
#include "../Device.hpp"
#include "OpenGLPipeline.hpp"
#include "OpenGLShader.hpp"

namespace FR8::LLGFX
{
    class OpenGLDevice : public Device
    {
    public:

        OpenGLDevice();
        ~OpenGLDevice();

        uint getGLBufferID(Buffer b) const;

        // TODO: enforce pipeline can't be deleted while bound?
        const OpenGLPipeline getOpenGLPipeline(Pipeline p) const;

        // overrides
        virtual std::unique_ptr<CommandQueue> createCommandQueue() override;

        virtual Buffer createBuffer(const BufferDescriptor &d) override;
        virtual void deleteBuffer(Buffer &buffer) override;
        virtual bool ownsBuffer(Buffer b) const override;

        virtual Pipeline createPipeline(const PipelineDescriptor& d) override;
        virtual void deletePipeline(Pipeline& p) override;
        virtual bool ownsPipeline(Pipeline p) const override;

        virtual Shader createShader(const ShaderDescriptor& d) override;
        virtual void deleteShader(Shader &s) override;
        virtual bool ownsShader(Shader s) const override;

        virtual ShaderSignature createShaderSignature(const ShaderSignatureDescriptor &d) override;
        virtual void deleteShaderSignature(ShaderSignature &s) override;

        virtual const char* getDebugName() const override;

    private:

        // TODO: recycle deleted buffers
        std::vector<uint> mBuffers;
        std::vector<OpenGLPipeline> mPipelines;
        std::vector<OpenGLShader> mShaders;

    };
}