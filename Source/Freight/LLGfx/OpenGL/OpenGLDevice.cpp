#include "OpenGLDevice.hpp"
#include "../Log/Log.hpp"
#include <glad/glad.h>

namespace FR8::LLGFX
{
    OpenGLDevice::OpenGLDevice()
    {
        mBuffers.push_back(0); // handle 0 is null buffer
    }


    OpenGLDevice::~OpenGLDevice()
    {
        for (uint buffer : mBuffers)
            glDeleteBuffers(1, &buffer);

        // TODO: delete shaders and textures
    }


    Buffer OpenGLDevice::createBuffer(const BufferDescriptor& d)
    {
        bool dynamic = true;
        if (d.writeFrequency == BufferDescriptor::WriteFrequency::ONCE)
            dynamic = false;

        GLenum usage;

        switch (d.writeFrequency) {
        case BufferDescriptor::WriteFrequency::OFTEN:
            switch (d.usage) {
            case BufferDescriptor::Usage::CPU_READ_GPU_WRITE: usage = GL_DYNAMIC_READ; break;
            case BufferDescriptor::Usage::CPU_WRITE_GPU_READ: usage = GL_DYNAMIC_DRAW; break;
            default: FR8_DBG_CRASH(); break;
            } break;
        case BufferDescriptor::WriteFrequency::ONCE:
            switch (d.usage) {
            case BufferDescriptor::Usage::CPU_READ_GPU_WRITE: usage = GL_STATIC_READ; break;
            case BufferDescriptor::Usage::CPU_WRITE_GPU_READ: usage = GL_STATIC_DRAW; break;
            default: FR8_DBG_CRASH(); break;
            } break;
        default: FR8_DBG_CRASH();
            break;
        }

        unsigned int bID;
        glGenBuffers(1, &bID);
        glBindBuffer(GL_ARRAY_BUFFER, bID);
        glBufferData(GL_ARRAY_BUFFER, d.size, d.data, usage);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        Buffer buffer;
        buffer.handle = (ID)mBuffers.size();
        buffer.debugName = d.debugName;
        mBuffers.push_back(bID);
        return buffer;
    }


    void OpenGLDevice::deleteBuffer(Buffer& buffer)
    {
        FR8_DBG_ASSERT(hasBuffer(buffer.handle), "Buffer [" << buffer.debugName << "] does not exist in device [" << getDebugName() << "]");
        glDeleteBuffers(1, &mBuffers[buffer.handle]);
        buffer.handle = 0;
    }


    Pipeline OpenGLDevice::createPipeline(const PipelineDescriptor& d)
    {
        FR8_DBG_CRASH();
    }


    void OpenGLDevice::deletePipeline(Pipeline& p)
    {
        FR8_DBG_CRASH();
    }


    ShaderSignature OpenGLDevice::createShaderSignature(const ShaderSignatureDescriptor& d)
    {
        FR8_DBG_CRASH();
    }


    void OpenGLDevice::deleteShaderSignature(ShaderSignature& s)
    {
        FR8_DBG_CRASH();
    }


    bool OpenGLDevice::hasBuffer(ID handle) const
    {
        if (handle != 0 && handle < (ID) mBuffers.size()) {
            if (mBuffers.at(handle) != 0) return true;
        }

        return false;
    }


    const char* OpenGLDevice::getDebugName()
    {
        return (const char*) glGetString(GL_RENDERER);
    }
}