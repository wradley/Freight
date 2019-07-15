#pragma once
#include "Types.hpp"

namespace FR8::LLGFX
{
    struct BufferDescriptor
    {
        BufferDescriptor() :
            size(0),
            data(nullptr),
            debugName("UNNAMED"),
            writeFrequency(WriteFrequency::ONCE),
            usage(Usage::CPU_READ_GPU_WRITE)
        {}

        u32 size;
        void* data;
        char* debugName;

        enum class WriteFrequency {
            ONCE, OFTEN
        } writeFrequency;

        enum class Usage {
            CPU_READ_GPU_WRITE,
            CPU_WRITE_GPU_READ,
        } usage;
    };
}