#pragma once

#define OGL_VERIFY_BUFFER(buff, devicePtr) FR8_DEBUG_ASSERT(devicePtr->ownsBuffer(buff), "Buffer [" << buff.debugName << "] does not exist in device [" << devicePtr->getDebugName() << "]");
#define OGL_VERIFY_SHADER(shdr, devicePtr) FR8_DEBUG_ASSERT(devicePtr->ownsShader(shdr), "Shader [" << shdr.debugName << "] does not exist in device [" << devicePtr->getDebugName() << "]");
#define OGL_VERIFY_SHADER_SIGNATURE(sig, devicePtr) FR8_DEBUG_ASSERT(devicePtr->ownsShaderSignature(sig), "Shader Signature [" << sig.debugName << "] does not exist in device [" << devicePtr->getDebugName() << "]");
#define OGL_VERIFY_PIPELINE(pipeline, devicePtr) FR8_DEBUG_ASSERT(devicePtr->ownsPipeline(pipeline), "Pipeline [" << pipeline.debugName << "] does not exist in device [" << devicePtr->getDebugName() << "]");
