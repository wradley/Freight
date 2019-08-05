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


    //void OpenGLCommandQueue::setPipeline(Pipeline p)
    //{
    //    OGL_VERIFY_PIPELINE(p, mDevice);

    //    mBoundPipeline = mDevice->getOpenGLPipeline(p);
    //    mPipelineHasChanged = true;
    //}


    //void OpenGLCommandQueue::setShaderConstant(uint sigParam, const void *src, uint size, uint dstOffset)
    //{
    //    //// verify with signature
    //    //auto &signaure = mDevice->getOpenGLShaderSignature(mBoundPipeline.shaderSignature);
    //    //auto constants = static_cast<OpenGLShaderConstants*>(mShaderParameters[sigParam].get());





    //    //float val;
    //    //memcpy(&val, &src, sizeof(i32));
    //    //const OpenGLShaderSignature &openGLSig = mDevice->getOpenGLShaderSignature(mBoundPipeline.shaderSignature);
    //    //const ShaderSignatureDescriptor &sig = openGLSig.shaderSignatureDescriptor;
    //    //FR8_DBG_ASSERT(sig.slots.size() > sIndex,
    //    //    "Signature index [" << sIndex << "] does not exist in pipeline [" << mBoundPipeline.debugName << "] shader signature");
    //    //FR8_DBG_ASSERT(sig.slots.at(sIndex).slotType == SignatureSlotDescriptor::SlotType::CONSTANT,
    //    //    "Signature index [" << sIndex << "] in pipeline [" << mBoundPipeline.debugName << "] is not of type CONSTANT");

    //    //const SignatureSlotDescriptor &constant = sig.slots.at(sIndex);
    //    //
    //    //// vertex shader
    //    //if (constant.access & LLGFX_VERTEX_SHADER_BIT) {
    //    //    OpenGLShader shader = mDevice->getOpenGLShader(mBoundPipeline.vertexShaderProgram);

    //    //    switch (constant.constantDescriptor.format) {
    //    //    case SignatureConstantDescriptor::Format::FLOAT: {
    //    //        float val;
    //    //        memcpy(&val, &src, sizeof(i32));
    //    //        glProgramUniform1f(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
    //    //    } break;
    //    //    case SignatureConstantDescriptor::Format::I32: {
    //    //        i32 val;
    //    //        memcpy(&val, &src, sizeof(i32));
    //    //        glProgramUniform1i(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
    //    //    } break;
    //    //    case SignatureConstantDescriptor::Format::U32: {
    //    //        u32 val;
    //    //        memcpy(&val, &src, sizeof(i32));
    //    //        glProgramUniform1ui(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
    //    //    } break;
    //    //    default: FR8_DBG_CRASH("Signature constant index [" << sIndex << "] unknown format in pipeline [" << mBoundPipeline.debugName << "]"); break;
    //    //    }
    //    //}

    //    //// fragment shader
    //    //if (constant.access & LLGFX_FRAGMENT_SHADER_BIT) {
    //    //    OpenGLShader shader = mDevice->getOpenGLShader(mBoundPipeline.fragmentShaderProgram);

    //    //    switch (constant.constantDescriptor.format) {
    //    //    case SignatureConstantDescriptor::Format::FLOAT: {
    //    //        float val;
    //    //        memcpy(&val, &src, sizeof(i32));
    //    //        glProgramUniform1f(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
    //    //    } break;
    //    //    case SignatureConstantDescriptor::Format::I32: {
    //    //        i32 val;
    //    //        memcpy(&val, &src, sizeof(i32));
    //    //        glProgramUniform1i(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
    //    //    } break;
    //    //    case SignatureConstantDescriptor::Format::U32: {
    //    //        u32 val;
    //    //        memcpy(&val, &src, sizeof(i32));
    //    //        glProgramUniform1ui(shader.shader, constant.constantDescriptor.shaderRegister + dstOffset, val);
    //    //    } break;
    //    //    default: FR8_DBG_CRASH("Signature constant index [" << sIndex << "] unknown format in pipeline [" << mBoundPipeline.debugName << "]"); break;
    //    //    }
    //    //}

    //}


    //void OpenGLCommandQueue::setShaderConstantBufferView(uint signatureIndex, ConstantBufferView c)
    //{
    //    FR8_DBG_CRASH("not implemented");
    //}


    //void OpenGLCommandQueue::setShaderViewTable(uint signatureIndex, ViewTable c)
    //{
    //    FR8_DBG_CRASH("not implemented");
    //}


    //void OpenGLCommandQueue::setVertexBuffer(Buffer b)
    //{
    //    OGL_VERIFY_BUFFER(b, mDevice);
    //    //glBindBuffer(GL_ARRAY_BUFFER, mDevice->getGLBufferID(b));
    //    glBindVertexBuffer(0, mDevice->getGLBufferID(b), 0, 24);
    //}


    //void OpenGLCommandQueue::setIndexBuffer(Buffer b)
    //{
    //    OGL_VERIFY_BUFFER(b, mDevice);
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mDevice->getGLBufferID(b));
    //}


    //void OpenGLCommandQueue::drawIndexed(u32 offset, u32 count)
    //{
    //    if (mPipelineHasChanged) {
    //        glBindVertexArray(mBoundPipeline.vertexArrayObject);
    //        glBindProgramPipeline(mBoundPipeline.programPipelineObject);
    //        mPipelineHasChanged = false;
    //    }

    //    glDrawElements(mBoundPipeline.primitiveTopology, count, mBoundPipeline.indexType, (void*)offset);
    //}

    
    void OpenGLCommandQueue::clear(const Flt4 &color)
    {
        glClearColor(color.at(0), color.at(1), color.at(2), color.at(3));
        glClear(GL_COLOR_BUFFER_BIT);
    }


    void OpenGLCommandQueue::submit(const DrawCommandSet &set)
    {
        // bind pipeline & vertex array
        OpenGLPipeline oglPipeline = mDevice->getOpenGLPipeline(set.pipeline);
        glBindVertexArray(oglPipeline.vertexArrayObject);
        glBindProgramPipeline(oglPipeline.programPipelineObject);

        // set common uniforms
        auto oglSignature = mDevice->getOpenGLShaderSignature(oglPipeline.shaderSignature);
        setShaderParameters(oglSignature.shaderSignatureDescriptor, set.parameters);

        for (const DrawCommand &drawCommand : set.drawCommands) 
        {
            // bind vertex buffers
            uint vbSlotIndex = 0;
            for (auto &vbSlot : drawCommand.vertexBufferSlots) {
                auto glBuffer = mDevice->getGLBufferID(vbSlot.buffer);
                glBindVertexBuffer(vbSlotIndex, glBuffer, vbSlot.offset, vbSlot.stride);
                ++vbSlotIndex;
            }

            // bind index buffers
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mDevice->getGLBufferID(drawCommand.indexBuffer));

            // set per draw uniforms
            setShaderParameters(oglSignature.shaderSignatureDescriptor, drawCommand.parameters);

            // draw
            GLenum indexFormat;
            switch (drawCommand.indexFormat) {
            case Format::R32_UINT: indexFormat = GL_UNSIGNED_INT; break;
            default: 
                FR8_DEBUG_CRASH("Unknown index format in draw command [" << LLGFX_GET_DEBUG_NAME(drawCommand) << "]");
                break;
            }
            glDrawElements(oglPipeline.primitiveTopology, drawCommand.indexCount, indexFormat, (void*)drawCommand.indexOffset);
            
            // unbind vertex buffers
            glBindVertexBuffers(0, vbSlotIndex, NULL, NULL, NULL);
        }

        // TODO: unbind all parameters

        // unbinds
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindProgramPipeline(0);
    }


    void OpenGLCommandQueue::commit()
    {}


    void OpenGLCommandQueue::setShaderParameters(const ShaderSignatureDescriptor &signature, const std::vector<ShaderParameter> &parameters)
    {
        for (auto &parameter : parameters) {
            // verify that signature has parameter
            FR8_DEBUG_ASSERT(signature.parameters.size() > parameter.index,
                "Index [" << parameter.index << "] does not exist in shader signature [" << LLGFX_GET_DEBUG_NAME(signature) << "]");

            switch (signature.parameters[parameter.index].parameterType)
            {
            case SignatureParameterDescriptor::ParameterType::CONSTANT:
                setShaderConstant(signature.parameters[parameter.index], parameter.constantParameter.src);
                break;
            default:
                FR8_DEBUG_CRASH("Unknown parameter type in shader signature [" << signature.debugName << "]");
                break;
            }
        }
    }


    void OpenGLCommandQueue::setShaderConstant(const SignatureParameterDescriptor &descriptor, const void *src)
    {
        FR8_DEBUG_ASSERT(descriptor.constantDescriptor.rowCount == 0, "rowCount of 0 in descriptor [" << descriptor.debugName << "]");
        GLint location = (GLint)descriptor.constantDescriptor.shaderRegister;

        switch (descriptor.constantDescriptor.rowCount)
        {
        case 1: // vector
            switch (descriptor.constantDescriptor.rowFormat) {
            case Format::R32_UINT: glUniform1ui(location, *(GLuint *)src); break;
            case Format::R32_SINT: glUniform1i(location, *(GLint *)src); break;
            case Format::R32_FLOAT: glUniform1f(location, *(GLfloat *)src); break;
            case Format::R32G32_UINT: glUniform2uiv(location, 2, (GLuint *)src); break;
            case Format::R32G32_SINT: glUniform2iv(location, 2, (GLint *)src); break;
            case Format::R32G32_FLOAT: glUniform2fv(location, 2, (GLfloat *)src); break;
            case Format::R32G32B32_UINT: glUniform3uiv(location, 3, (GLuint *)src); break;
            case Format::R32G32B32_SINT: glUniform3iv(location, 3, (GLint *)src); break;
            case Format::R32G32B32_FLOAT: glUniform3fv(location, 3, (GLfloat *)src); break;
            case Format::R32G32B32A32_UINT: glUniform4uiv(location, 4, (GLuint *)src); break;
            case Format::R32G32B32A32_SINT: glUniform4iv(location, 4, (GLint *)src); break;
            case Format::R32G32B32A32_FLOAT: glUniform4fv(location, 4, (GLfloat *)src); break;
            default: FR8_DEBUG_CRASH("Unknown format in SignatureConstantDescriptor::rowForamt [" << descriptor.debugName << "]"); break;
            } break;
        case 2: // matrices
            switch (descriptor.constantDescriptor.rowFormat) {
            case Format::R32G32_UINT: glUniformMatrix2fv(location, 1, false, (GLfloat *)src); break;
            case Format::R32G32B32_UINT: glUniformMatrix2x3fv(location, 1, false, (GLfloat *)src); break;
            case Format::R32G32B32A32_UINT: glUniformMatrix2x4fv(location, 1, false, (GLfloat *)src); break;
            default: FR8_DEBUG_CRASH("Unknown format in SignatureConstantDescriptor::rowForamt [" << descriptor.debugName << "]"); break; 
            }
        case 3:
            switch (descriptor.constantDescriptor.rowFormat) {
            case Format::R32G32_UINT: glUniformMatrix3x2fv(location, 1, false, (GLfloat *)src); break;
            case Format::R32G32B32_UINT: glUniformMatrix3fv(location, 1, false, (GLfloat *)src); break;
            case Format::R32G32B32A32_UINT: glUniformMatrix3x4fv(location, 1, false, (GLfloat *)src); break;
            default: FR8_DEBUG_CRASH("Unknown format in SignatureConstantDescriptor::rowForamt [" << descriptor.debugName << "]"); break;
            }
        case 4:
            switch (descriptor.constantDescriptor.rowFormat) {
            case Format::R32G32_UINT: glUniformMatrix4x2fv(location, 1, false, (GLfloat *)src); break;
            case Format::R32G32B32_UINT: glUniformMatrix3x4fv(location, 1, false, (GLfloat *)src); break;
            case Format::R32G32B32A32_UINT: glUniformMatrix4fv(location, 1, false, (GLfloat *)src); break;
            default: FR8_DEBUG_CRASH("Unknown format in SignatureConstantDescriptor::rowForamt [" << descriptor.debugName << "]"); break;
            }
        default:
            FR8_DEBUG_CRASH("rowCount of [" << descriptor.constantDescriptor.rowCount << "] in SignatureConstantDescriptor [" << descriptor.debugName << "]");
            break;
        }

        FR8_DEBUG_CRASH("rowCount of [" << descriptor.constantDescriptor.rowCount << "] in SignatureConstantDescriptor [" << descriptor.debugName << "]");
    }
}
