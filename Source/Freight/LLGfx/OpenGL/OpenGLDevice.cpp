#include "OpenGLDevice.hpp"
#include "OpenGLCommandQueue.hpp"
#include "OpenGLErrorChecks.hpp"
#include "../Log/Log.hpp"
#include <glad/glad.h>

void GLAPIENTRY MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam)
{
    const char *sevarityStr;
    switch (severity) {
    case GL_DEBUG_SEVERITY_NOTIFICATION: sevarityStr = "notification"; break;
    case GL_DEBUG_SEVERITY_LOW: sevarityStr = "low"; break;
    case GL_DEBUG_SEVERITY_MEDIUM: sevarityStr = "medium"; break;
    case GL_DEBUG_SEVERITY_HIGH: sevarityStr = "high"; break;
    default: sevarityStr = "unknown"; break;
    }

    if (type == GL_DEBUG_TYPE_ERROR) {
        FR8_DBG_ERR("OpenGL Debug\n" << message);
    }

    else {
        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
            FR8_DBG_LOG("OpenGL Debug\n" << message);
        }
        else if (severity == GL_DEBUG_SEVERITY_LOW || severity == GL_DEBUG_SEVERITY_MEDIUM) {
            FR8_DBG_WARN("OpenGL Debug\n" << message);
        }
        else {
            FR8_DBG_ERR("OpenGL Debug\n" << message);
        }
    }
}

namespace FR8::LLGFX
{
    OpenGLDevice::OpenGLDevice()
    {
        // enable debug output
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);

        mBuffers.push_back(0); // handle 0 is null buffer
        mPipelines.push_back(OpenGLPipeline()); // handle 0 is null buffer
        mShaders.push_back(OpenGLShader()); // handle 0 is null buffer
        mShaderSignatures.push_back(OpenGLShaderSignature());
    }


    OpenGLDevice::~OpenGLDevice()
    {
        for (uint buffer : mBuffers)
            glDeleteBuffers(1, &buffer);

        // TODO: delete shaders and textures
    }


    uint OpenGLDevice::getGLBufferID(Buffer b) const
    {
        OGL_VERIFY_BUFFER(b, this);
        return mBuffers[b.handle];
    }


    const OpenGLPipeline OpenGLDevice::getOpenGLPipeline(Pipeline p) const
    {
        OGL_VERIFY_PIPELINE(p, this);
        return mPipelines[p.handle];
    }


    const OpenGLShader OpenGLDevice::getOpenGLShader(Shader s) const
    {
        OGL_VERIFY_SHADER(s, this);
        return mShaders[s.handle];
    }


    const OpenGLShaderSignature &OpenGLDevice::getOpenGLShaderSignature(ShaderSignature s) const
    {
        OGL_VERIFY_SHADER_SIGNATURE(s, this);
        return mShaderSignatures[s.handle];
    }


    std::unique_ptr<CommandQueue> OpenGLDevice::createCommandQueue()
    {
        auto cmdQueue = new OpenGLCommandQueue(this);
        return std::unique_ptr<CommandQueue>(cmdQueue);
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
            default: FR8_DBG_CRASH("Unknown usage in buffer descriptor [" << d.debugName << "]"); break;
            } break;
        case BufferDescriptor::WriteFrequency::ONCE:
            switch (d.usage) {
            case BufferDescriptor::Usage::CPU_READ_GPU_WRITE: usage = GL_STATIC_READ; break;
            case BufferDescriptor::Usage::CPU_WRITE_GPU_READ: usage = GL_STATIC_DRAW; break;
            default: FR8_DBG_CRASH("Unknown usage in buffer descriptor [" << d.debugName << "]"); break;
            } break;
        default: FR8_DBG_CRASH("Unknown type in buffer descriptor [" << d.debugName << "]");
            break;
        }

        unsigned int bID;
        glGenBuffers(1, &bID);
        int prev;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prev);
        glBindBuffer(GL_ARRAY_BUFFER, bID);
        glBufferData(GL_ARRAY_BUFFER, d.size, d.data, usage);
        glBindBuffer(GL_ARRAY_BUFFER, (GLuint)prev);

        Buffer buffer;
        buffer.handle = (ID)mBuffers.size();
        buffer.debugName = d.debugName;
        mBuffers.push_back(bID);
        return buffer;
    }


    void OpenGLDevice::deleteBuffer(Buffer& buffer)
    {
        OGL_VERIFY_BUFFER(buffer, this);
        glDeleteBuffers(1, &mBuffers[buffer.handle]);
        buffer.handle = 0;
    }


    bool OpenGLDevice::ownsBuffer(Buffer b) const
    {
        if (b.handle != 0 && b.handle < (ID)mBuffers.size()) {
            if (mBuffers.at(b.handle) != 0) return true;
        }

        return false;
    }


    Pipeline OpenGLDevice::createPipeline(const PipelineDescriptor& d)
    {
        OGL_VERIFY_SHADER(d.vertexShader, this);
        OGL_VERIFY_SHADER(d.fragmentShader, this);

        GLenum topology;
        switch (d.primitiveTopology) {
        case Topology::TRIANGLE: topology = GL_TRIANGLES; break;
        default: FR8_DBG_CRASH("Unknown primitive topology in pipeline descriptor [" << d.debugName << "]"); break;
        }

        GLenum indexFormat;
        switch (d.indexFormat) {
        case Format::R32_UINT: indexFormat = GL_UNSIGNED_INT; break;
        default: FR8_DBG_CRASH("Unknown index format in pipeline descriptor [" << d.debugName << "]"); break;
        }

        OpenGLPipeline ret;
        ret.primitiveTopology = topology;
        ret.indexType = indexFormat;
        ret.valid = true;
        ret.vertexShaderProgram = d.vertexShader;
        ret.fragmentShaderProgram = d.fragmentShader;
        ret.shaderSignature = d.shaderSignature;
        ret.debugName = d.debugName;

        // create shader program pipeline object
        glGenProgramPipelines(1, &ret.programPipelineObject);
        glBindProgramPipeline(ret.programPipelineObject);
        glUseProgramStages(ret.programPipelineObject, GL_VERTEX_SHADER_BIT, mShaders[d.vertexShader.handle].shader);
        glUseProgramStages(ret.programPipelineObject, GL_FRAGMENT_SHADER_BIT, mShaders[d.fragmentShader.handle].shader);
        

        // create vertex array object (vertex bindings)
        glGenVertexArrays(1, &ret.vertexArrayObject);
        glBindVertexArray(ret.vertexArrayObject);

        uint i = 0;
        for (const InputElementDescriptor &element : d.inputLayout.elements) {

            GLint size;
            GLenum type;

            switch (element.format)
            {
            case Format::R32_FLOAT: size = 1; type = GL_FLOAT; break;
            case Format::R32G32_FLOAT: size = 2; type = GL_FLOAT; break;
            case Format::R32G32B32_FLOAT: size = 3; type = GL_FLOAT; break;
            case Format::R32G32B32A32_FLOAT: size = 4; type = GL_FLOAT; break;
            default: FR8_DBG_CRASH("Unknown format in InputElementDescriptor [" << i << "] in Pipeline desciptor [" << d.debugName << "]"); break;
            }

            glEnableVertexArrayAttrib(ret.vertexArrayObject, element.index);
            glVertexArrayAttribFormat(ret.vertexArrayObject, element.index, size, type, element.normalized, element.offset);
            glVertexArrayAttribBinding(ret.vertexArrayObject, element.index, 0);
            ++i;
        }


        Pipeline pipeline;
        pipeline.handle = (ID)mPipelines.size();
        pipeline.debugName = d.debugName;
        mPipelines.push_back(ret);
        return pipeline;
    }


    void OpenGLDevice::deletePipeline(Pipeline& p)
    {
        OGL_VERIFY_PIPELINE(p, this);
        mPipelines[p.handle].valid = false;
    }


    bool OpenGLDevice::ownsPipeline(Pipeline p) const
    {
        if (p.handle != 0 && p.handle < (ID)mPipelines.size()) {
            if (mPipelines.at(p.handle).valid) return true;
        }

        return false;
    }


    Shader OpenGLDevice::createShader(const ShaderDescriptor &d)
    {
        GLenum shaderType;
        switch (d.type)
        {
        case ShaderType::VERTEX_SHADER: shaderType = GL_VERTEX_SHADER; break;
        case ShaderType::FRAGMENT_SHADER: shaderType = GL_FRAGMENT_SHADER; break;
        default: FR8_DBG_CRASH("Unknown type in shader descriptor [" << d.debugName << "]"); break;
        }

        auto glCode = static_cast<const OpenGLShaderCode*>(d.code.get());
        const char *code = glCode->code.c_str();
        uint program = glCreateShaderProgramv(shaderType, 1, &code);

        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            FR8_DBG_ASSERT(false, "Error linking shader\n" << infoLog);
        }

        Shader ret;
        ret.debugName = d.debugName;
        ret.handle = (ID)mShaders.size();
        OpenGLShader glShader;
        glShader.shader = program;
        glShader.valid = true;
        mShaders.push_back(glShader);
        return ret;
    }


    void OpenGLDevice::deleteShader(Shader &s)
    {
        OGL_VERIFY_SHADER(s, this);
        mShaders[s.handle].valid = false;
    }


    bool OpenGLDevice::ownsShader(Shader s) const
    {
        if (s.handle != 0 && s.handle < (ID)mShaders.size()) {
            if (mShaders.at(s.handle).valid) return true;
        }

        return false;
    }


    ShaderSignature OpenGLDevice::createShaderSignaure(const ShaderSignatureDescriptor &d)
    {
        OpenGLShaderSignature oglSig;
        oglSig.shaderSignatureDescriptor = d;
        oglSig.shaderSignatureDescriptor.slots.shrink_to_fit();
        oglSig.valid = true;
        oglSig.debugName = d.debugName;

        ShaderSignature ret;
        ret.debugName = d.debugName;
        ret.handle = (ID)mShaderSignatures.size();
        mShaderSignatures.push_back(oglSig);

        return ret;
    }


    void OpenGLDevice::deleteShaderSignature(ShaderSignature s)
    {
        OGL_VERIFY_SHADER_SIGNATURE(s, this);
        mShaderSignatures[s.handle].valid = false;
    }


    bool OpenGLDevice::ownsShaderSignature(ShaderSignature s) const
    {
        if (s.handle < (ID)mShaderSignatures.size()) {
            if (mShaderSignatures[s.handle].valid) {
                return true;
            }
        }
        return false;
    }


    const char* OpenGLDevice::getDebugName() const
    {
        return (const char*) glGetString(GL_RENDERER);
    }
}