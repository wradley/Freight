#include "OpenGLCommandQueue.hpp"
#include "OpenGLDevice.hpp"
#include "OpenGLPipeline.hpp"
#include "OpenGLErrorChecks.hpp"
#include <glad/glad.h>
#include "../../Log/Log.hpp"


namespace FR8::LLGFX
{
    OpenGLCommandQueue::OpenGLCommandQueue(OpenGLDevice *device) : mDevice(device), mBoundPipeline{}
    {
        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);
    }
    
    
    OpenGLCommandQueue::~OpenGLCommandQueue()
    {}


    void OpenGLCommandQueue::setPipeline(Pipeline p)
    {
        // disable attributes
        int i = 0;
        for (InputElementDescriptor &element : mBoundPipeline.inputLayout.elements) {
            glDisableVertexAttribArray(i++);
        }

        mBoundPipeline = mDevice->getOpenGLPipeline(p);
        glBindProgramPipeline(mBoundPipeline.pipeline);

        // enable attributes
        i = 0;
        for (InputElementDescriptor &element : mBoundPipeline.inputLayout.elements) {

            GLint size;
            GLenum type;

            switch (element.format)
            {
            case Format::R32_FLOAT: size = 1; type = GL_FLOAT; break;
            case Format::R32G32_FLOAT: size = 2; type = GL_FLOAT; break;
            case Format::R32G32B32_FLOAT: size = 3; type = GL_FLOAT; break;
            case Format::R32G32B32A32_FLOAT: size = 4; type = GL_FLOAT; break;
            default: FR8_DBG_CRASH("Unknown format in InputElementDescriptor [" << i << "] in Pipeline [" << p.debugName << "]"); break;
            }

            glEnableVertexAttribArray(i);
            glVertexAttribFormat(element.index, size, type, element.normalized, element.offset);
            glVertexAttribBinding(i, 0);
            ++i;
        }
    }


    void OpenGLCommandQueue::setShaderConstant(uint index, i32 src, u32 dstOffset)
    {
        FR8_DBG_CRASH("not implemented");
    }


    void OpenGLCommandQueue::setShaderConstantBufferView(uint index, ConstantBufferView c)
    {
        FR8_DBG_CRASH("not implemented");
    }


    void OpenGLCommandQueue::setShaderViewTable(uint index, ViewTable c)
    {
        FR8_DBG_CRASH("not implemented");
    }


    void OpenGLCommandQueue::setVertexBuffer(Buffer b)
    {
        OGL_VERIFY_BUFFER(b, mDevice);
        //glBindBuffer(GL_ARRAY_BUFFER, mDevice->getGLBufferID(b));
        glBindVertexBuffer(0, mDevice->getGLBufferID(b), 0, 6);
    }


    void OpenGLCommandQueue::setIndexBuffer(Buffer b)
    {
        OGL_VERIFY_BUFFER(b, mDevice);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mDevice->getGLBufferID(b));
    }


    void OpenGLCommandQueue::drawIndexed(u32 offset, u32 count)
    {
        glDrawElements(mBoundPipeline.primitiveTopology, count, mBoundPipeline.indexType, (void*)offset);
    }

    
    void OpenGLCommandQueue::clear(const Flt4 &color)
    {
        glClearColor(color.at(0), color.at(1), color.at(2), color.at(3));
        glClear(GL_COLOR_BUFFER_BIT);
    }


    void OpenGLCommandQueue::commit()
    {}


    void OpenGLCommandQueue::reset()
    {
    }
}
