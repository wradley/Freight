#include "OpenGLCommandQueue.hpp"
#include "OpenGLDevice.hpp"
#include "OpenGLPipeline.hpp"
#include "OpenGLErrorChecks.hpp"
#include <glad/glad.h>
#include "../../Log/Log.hpp"


namespace FR8::LLGFX
{
    OpenGLCommandQueue::OpenGLCommandQueue(OpenGLDevice *device) : mDevice(device), mBoundPipeline{}
    {}
    
    
    OpenGLCommandQueue::~OpenGLCommandQueue()
    {}


    void OpenGLCommandQueue::setPipeline(Pipeline p)
    {
        OGL_VERIFY_PIPELINE(p, mDevice);

        mBoundPipeline = mDevice->getOpenGLPipeline(p);
        mPipelineHasChanged = true;
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
        glBindVertexBuffer(0, mDevice->getGLBufferID(b), 0, 24);
    }


    void OpenGLCommandQueue::setIndexBuffer(Buffer b)
    {
        OGL_VERIFY_BUFFER(b, mDevice);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mDevice->getGLBufferID(b));
    }


    void OpenGLCommandQueue::drawIndexed(u32 offset, u32 count)
    {
        if (mPipelineHasChanged) {
            glBindVertexArray(mBoundPipeline.vertexArrayObject);
            glBindProgramPipeline(mBoundPipeline.programPipelineObject);
            mPipelineHasChanged = false;
        }

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
