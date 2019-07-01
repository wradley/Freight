#pragma once

namespace FR8::LLGFX
{
    class Device
    {
    public:

        struct BufferDescriptor
        {
            size_t size;
        };

        virtual size_t createBuffer(const BufferDescriptor &d) = 0;
        virtual void deleteBuffer(size_t) = 0;

    };
}