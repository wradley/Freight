#pragma once
#include "ShaderSignatureDescriptor.hpp"
#include "../Log/Log.hpp"

namespace FR8::LLGFX
{
    SignatureSlotDescriptor::SignatureSlotDescriptor() :
        slotType(SlotType::NIL), 
        access(LLGFX_NIL_SHADER_BIT), 
        constantDescriptor{}, 
        viewDescriptor{}, 
        viewTableDescriptor{}
    {}


    SignatureSlotDescriptor::SignatureSlotDescriptor(const SignatureSlotDescriptor &s) :
        slotType(s.slotType), 
        access(s.access), 
        constantDescriptor{}, 
        viewDescriptor{}, 
        viewTableDescriptor{}
    {
        switch (s.slotType) {
        case SlotType::NIL: break;
        case SlotType::CONSTANT: constantDescriptor = s.constantDescriptor; break;
        case SlotType::VIEW: viewDescriptor = s.viewDescriptor; break;
        case SlotType::VIEW_TABLE: viewTableDescriptor = s.viewTableDescriptor; break;
        default: FR8_DBG_CRASH("Unknown slot type");
        }
    }


    SignatureSlotDescriptor &SignatureSlotDescriptor::operator=(const SignatureSlotDescriptor &s)
    {
        slotType = s.slotType;
        access = s.access;

        switch (s.slotType) {
        case SlotType::NIL: break;
        case SlotType::CONSTANT: constantDescriptor = s.constantDescriptor; break;
        case SlotType::VIEW: viewDescriptor = s.viewDescriptor; break;
        case SlotType::VIEW_TABLE: viewTableDescriptor = s.viewTableDescriptor; break;
        default: FR8_DBG_CRASH("Unknown slot type");
        }

        return *this;
    }


    SignatureSlotDescriptor::~SignatureSlotDescriptor()
    {
        switch (slotType) {
        case SlotType::NIL: break;
        case SlotType::CONSTANT: constantDescriptor.~SignatureConstantDescriptor(); break;
        case SlotType::VIEW: viewDescriptor.~SignatureViewDescriptor(); break;
        case SlotType::VIEW_TABLE: viewTableDescriptor.~SignatureViewTableDescriptor(); break;
        default: FR8_DBG_CRASH("Unknown slot type");
        }
    }
}