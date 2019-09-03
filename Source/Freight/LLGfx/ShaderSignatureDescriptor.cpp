#pragma once
#include "ShaderSignatureDescriptor.hpp"
#include "../Log/Log.hpp"

namespace FR8::LLGFX
{
    SignatureParameterDescriptor::SignatureParameterDescriptor() :
        parameterType(ParameterType::NIL), 
        access(LLGFX_NIL_SHADER_BIT), 
        debugName(nullptr),
        constantDescriptor{}
    {}


    SignatureParameterDescriptor::SignatureParameterDescriptor(const SignatureParameterDescriptor &s) :
        parameterType(s.parameterType), 
        access(s.access), 
        debugName(nullptr),
        constantDescriptor{}
    {
        switch (s.parameterType) {
        case ParameterType::NIL: break;
        case ParameterType::CONSTANT: constantDescriptor = s.constantDescriptor; break;
        case ParameterType::VIEW: viewDescriptor = s.viewDescriptor; break;
        case ParameterType::VIEW_TABLE: viewTableDescriptor = s.viewTableDescriptor; break;
        default: FR8_DEBUG_CRASH("Unknown slot type");
        }
    }


    SignatureParameterDescriptor &SignatureParameterDescriptor::operator=(const SignatureParameterDescriptor &s)
    {
        parameterType = s.parameterType;
        access = s.access;
        debugName = nullptr;

        switch (s.parameterType) {
        case ParameterType::NIL: break;
        case ParameterType::CONSTANT: constantDescriptor = s.constantDescriptor; break;
        case ParameterType::VIEW: viewDescriptor = s.viewDescriptor; break;
        case ParameterType::VIEW_TABLE: viewTableDescriptor = s.viewTableDescriptor; break;
        default: FR8_DEBUG_CRASH("Unknown slot type");
        }

        return *this;
    }


    SignatureParameterDescriptor::~SignatureParameterDescriptor()
    {
        switch (parameterType) {
        case ParameterType::NIL: break;
        case ParameterType::CONSTANT: constantDescriptor.~SignatureConstantDescriptor(); break;
        case ParameterType::VIEW: viewDescriptor.~SignatureViewDescriptor(); break;
        case ParameterType::VIEW_TABLE: viewTableDescriptor.~SignatureViewTableDescriptor(); break;
        default: FR8_DEBUG_CRASH("Unknown slot type");
        }
    }
}
