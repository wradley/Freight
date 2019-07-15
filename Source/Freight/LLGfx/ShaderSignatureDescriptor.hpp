#pragma once
#include "Types.hpp"

namespace FR8::LLGFX
{
    struct SignatureSlotDescriptor
    {
        enum class Type { CONSTANT, VIEW, VIEW_TABLE };
        virtual Type getType() const = 0;

        ShaderType access;
    };


    struct SignatureConstantDescriptor : public SignatureSlotDescriptor
    {
        virtual Type getType() const override { 
            return SignatureSlotDescriptor::Type::CONSTANT;
        }
    };


    struct SignatureViewDescriptor : public SignatureSlotDescriptor
    {
        virtual Type getType() const override {
            return SignatureSlotDescriptor::Type::VIEW;
        }

        enum class ViewType { CONSTANT_BUFFER_VIEW };
        virtual ViewType getViewType() const = 0;
    };


    struct SignatureConstantBufferViewDescriptor : public SignatureViewDescriptor
    {
        virtual ViewType getViewType() const override {
            return SignatureViewDescriptor::ViewType::CONSTANT_BUFFER_VIEW;
        }
    };


    struct SignatureViewTableDescriptor : public SignatureSlotDescriptor
    {
        virtual Type getType() const override {
            return SignatureSlotDescriptor::Type::VIEW_TABLE;
        }

        SignatureViewDescriptor* viewDescriptors;
        uint viewDescriptorCount;
    };

    struct ShaderSignatureDescriptor
    
   
{
        SignatureSlotDescriptor* slots;
        uint slotCount;
    };
}