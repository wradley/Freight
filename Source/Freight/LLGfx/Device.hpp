#pragma once
#include <vector>
#include <memory>
#include "Types.hpp"
#include "BufferDescriptor.hpp"
#include "PipelineDescriptor.hpp"
#include "ShaderDescriptor.hpp"
#include "ShaderSignatureDescriptor.hpp"

namespace FR8::LLGFX
{
    class CommandQueue;

    class Device
    {
    public:

        virtual ~Device() {}

        virtual std::unique_ptr<CommandQueue> createCommandQueue() = 0;

        //virtual void mapBufferMemory(Buffer b, uint offset, uint size, void **out) = 0;

        virtual Buffer createBuffer(const BufferDescriptor &d) = 0;
        virtual void deleteBuffer(Buffer &b) = 0;
        virtual bool ownsBuffer(Buffer b) const = 0;

        virtual Pipeline createPipeline(const PipelineDescriptor &d) = 0;
        virtual void deletePipeline(Pipeline &p) = 0;

        virtual Shader createShader(const ShaderDescriptor &d) = 0;
        virtual void deleteShader(Shader &d) = 0;

        virtual ShaderSignature createShaderSignature(const ShaderSignatureDescriptor &d) = 0;
        virtual void deleteShaderSignature(ShaderSignature &s) = 0;

        virtual const char* getDebugName() = 0;

    };
}