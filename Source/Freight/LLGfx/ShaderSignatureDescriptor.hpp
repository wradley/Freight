#pragma once
#include <vector>
#include "Types.hpp"

namespace FR8::LLGFX
{
    // constant ---------------------------------

    struct SignatureConstantDescriptor
    {
        uint shaderRegister;
        uint registerSpace;

        Format rowFormat;

        // 1 = 1xF (vector), 2 = 2xF matrix (where F is rowFormat), ect...
        uint rowCount;
    };


    // views ------------------------------------

    struct SignatureConstantBufferViewDescriptor
    {
    };


    struct SignatureViewDescriptor
    {
        enum class ViewType { CONSTANT_BUFFER_VIEW } viewType;
        union {
            SignatureConstantBufferViewDescriptor signatureCBVDescriptor;
        };
    };


    // table ------------------------------------

    struct SignatureViewTableDescriptor
    {
        std::vector<SignatureViewDescriptor> viewDescriptors;
    };


    // signature --------------------------------

    struct SignatureParameterDescriptor
    {
        SignatureParameterDescriptor();
        SignatureParameterDescriptor(const SignatureParameterDescriptor &s);
        SignatureParameterDescriptor & operator= (const SignatureParameterDescriptor &s);
        ~SignatureParameterDescriptor();

        enum class ParameterType { NIL, CONSTANT, VIEW, VIEW_TABLE } parameterType;
        ShaderTypeBit access;
        const char *debugName;

        union {
            SignatureConstantDescriptor constantDescriptor;
            SignatureViewDescriptor viewDescriptor;
            SignatureViewTableDescriptor viewTableDescriptor;
        };

    };


    struct ShaderSignatureDescriptor
    {
        std::vector<SignatureParameterDescriptor> parameters;
        const char *debugName;
    };
}