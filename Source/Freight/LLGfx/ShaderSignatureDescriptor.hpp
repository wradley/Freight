#pragma once
#include <vector>
#include "Types.hpp"

namespace FR8::LLGFX
{
    // constant ---------------------------------

    struct SignatureConstantDescriptor
    {
        enum class Format {
            FLOAT,
            I32,
            U32
        } format;

        uint shaderRegister;
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

    struct SignatureSlotDescriptor
    {
        SignatureSlotDescriptor();
        SignatureSlotDescriptor(const SignatureSlotDescriptor &s);
        SignatureSlotDescriptor& operator= (const SignatureSlotDescriptor &s);
        ~SignatureSlotDescriptor();

        enum class SlotType { NIL, CONSTANT, VIEW, VIEW_TABLE } slotType;
        ShaderTypeBit access;

        union {
            SignatureConstantDescriptor constantDescriptor;
            SignatureViewDescriptor viewDescriptor;
            SignatureViewTableDescriptor viewTableDescriptor;
        };

    };


    struct ShaderSignatureDescriptor
    {
        std::vector<SignatureSlotDescriptor> slots;
        const char *debugName;
    };
}