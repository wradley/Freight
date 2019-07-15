#include "OpenGLCommandQueue.hpp"
#include "OpenGLDevice.hpp"
#include "OpenGLPipeline.hpp"
#include <glad/glad.h>
#include "../../Log/Log.hpp"

#define VERIFY_BUFFER(buff, device) FR8_DBG_ASSERT(mDevice->ownsBuffer(buff), "Buffer [" << buff.debugName << "] does not exist in device [" << device->getDebugName() << "]");

namespace FR8::LLGFX
{
    OpenGLCommandQueue::OpenGLCommandQueue(OpenGLDevice *device) : mDevice(device), mBoundPipeline(0)
    {}
    
    
    OpenGLCommandQueue::~OpenGLCommandQueue()
    {}


    void OpenGLCommandQueue::setPipeline(Pipeline p)
    {
        FR8_DBG_CRASH();
        mBoundPipeline = mDevice->getOpenGLPipeline(p);
    }


    void OpenGLCommandQueue::setShaderConstant(uint index, i32 src, u32 dstOffset)
    {
        FR8_DBG_CRASH();
    }


    void OpenGLCommandQueue::setShaderConstantBufferView(uint index, ConstantBufferView c)
    {
        FR8_DBG_CRASH();
    }


    void OpenGLCommandQueue::setShaderViewTable(uint index, ViewTable c)
    {
        FR8_DBG_CRASH();
    }


    void OpenGLCommandQueue::setVertexBuffer(Buffer b)
    {
        VERIFY_BUFFER(b, mDevice);
        glBindBuffer(GL_ARRAY_BUFFER, mDevice->getGLBufferID(b));
    }


    void OpenGLCommandQueue::setIndexBuffer(Buffer b)
    {
        VERIFY_BUFFER(b, mDevice);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mDevice->getGLBufferID(b));
    }


    void OpenGLCommandQueue::drawIndexed(u32 offset, u32 count)
    {
        GLenum mode = 0;
        switch (mBoundPipeline->primitiveTopology) {
        case Topology::TRIANGLE: mode = GL_TRIANGLES; break;
        default: FR8_DBG_CRASH();  break;
        }

        GLenum type = 0;
        switch (mBoundPipeline->indexType) {
        case FR8::LLGFX::Format::R32_UINT: type = GL_UNSIGNED_INT; break;
        default: FR8_DBG_CRASH(); break;
        }

        glDrawElements(mode, count, type, (void*)offset);
    }


    void OpenGLCommandQueue::commit()
    {}


    void OpenGLCommandQueue::reset()
    {
        mBoundPipeline = nullptr;
    }
}
