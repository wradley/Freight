#pragma once

namespace FR8::LLGFX
{
    class CmdBuffer
    {
    public:

        virtual void setRenderTarget(size_t rt) = 0;
        virtual void setVertexBuffer(size_t vb, size_t index) = 0;
        virtual void setFragmentBuffer(size_t vb, size_t index) = 0;
        virtual void setVertexTexture(size_t vb, size_t index) = 0;
        virtual void setFragmentTexture(size_t vb, size_t index) = 0;
        virtual void draw() = 0;

    };
}