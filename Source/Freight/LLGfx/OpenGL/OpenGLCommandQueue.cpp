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


    void OpenGLCommandQueue::setShaderConstant(uint sIndex, i32 src, u32 dstOffset)
    {
        //FR8_DBG_CRASH("not implemented");
        //glUniform1i(index + dstOffset, src);
        OGL_VERIFY_SHADER(mBoundPipeline.vertexShaderProgram, mDevice);
        OGL_VERIFY_SHADER(mBoundPipeline.fragmentShaderProgram, mDevice);

        
        OpenGLShader fragmentShader = mDevice->getOpenGLShader(mBoundPipeline.fragmentShaderProgram);

        float val;
        memcpy(&val, &src, sizeof(i32));
        const OpenGLShaderSignature &openGLSig = mDevice->getOpenGLShaderSignature(mBoundPipeline.shaderSignature);
        const ShaderSignatureDescriptor &sig = openGLSig.shaderSignatureDescriptor;
        FR8_DBG_ASSERT(sig.slots.size() > sIndex,
            "Signature index [" << sIndex << "] does not exist in pipeline [" << mBoundPipeline.debugName << "] shader signature");
        FR8_DBG_ASSERT(sig.slots.at(sIndex).slotType == SignatureSlotDescriptor::SlotType::CONSTANT,
            "Signature index [" << sIndex << "] in pipeline [" << mBoundPipeline.debugName << "] is not of type CONSTANT");

        const SignatureSlotDescriptor &constant = sig.slots.at(sIndex);
        
        // vertex shader
        if (constant.access & LLGFX_VERTEX_SHADER_BIT) {
            OpenGLShader shader = mDevice->getOpenGLShader(mBoundPipeline.vertexShaderProgram);

            switch (constant.constantDescriptor.format) {
            case SignatureConstantDescriptor::Format::FLOAT: {
                float val;
                memcpy(&val, &src, sizeof(i32));
                glProgramUniform1f(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
            } break;
            case SignatureConstantDescriptor::Format::I32: {
                i32 val;
                memcpy(&val, &src, sizeof(i32));
                glProgramUniform1i(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
            } break;
            case SignatureConstantDescriptor::Format::U32: {
                u32 val;
                memcpy(&val, &src, sizeof(i32));
                glProgramUniform1ui(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
            } break;
            default: FR8_DBG_CRASH("Signature constant index [" << sIndex << "] unknown format in pipeline [" << mBoundPipeline.debugName << "]"); break;
            }
        }

        // fragment shader
        if (constant.access & LLGFX_FRAGMENT_SHADER_BIT) {
            OpenGLShader shader = mDevice->getOpenGLShader(mBoundPipeline.fragmentShaderProgram);

            switch (constant.constantDescriptor.format) {
            case SignatureConstantDescriptor::Format::FLOAT: {
                float val;
                memcpy(&val, &src, sizeof(i32));
                glProgramUniform1f(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
            } break;
            case SignatureConstantDescriptor::Format::I32: {
                i32 val;
                memcpy(&val, &src, sizeof(i32));
                glProgramUniform1i(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
            } break;
            case SignatureConstantDescriptor::Format::U32: {
                u32 val;
                memcpy(&val, &src, sizeof(i32));
                glProgramUniform1ui(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
            } break;
            default: FR8_DBG_CRASH("Signature constant index [" << sIndex << "] unknown format in pipeline [" << mBoundPipeline.debugName << "]"); break;
            }
        }

    }


    void OpenGLCommandQueue::setShaderConstantBufferView(uint signatureIndex, ConstantBufferView c)
    {
        FR8_DBG_CRASH("not implemented");
    }


    void OpenGLCommandQueue::setShaderViewTable(uint signatureIndex, ViewTable c)
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
