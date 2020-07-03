#include "Node2D.hpp"

namespace fr::gfx
{
    void Node2D::draw(const Mat3 &projViewParent, u8 stencilValue)
    {
        FR_DEBUG_ASSERT(stencilValue < 255, "Cannot have a depth of more that 256 in tree.")
        ++stencilValue;
        
        drawStencil(projViewParent, stencilValue);
        
        Mat3 mat = projViewParent * getLocalMatrix();
        
        for (auto &drawable : mDrawables)
            drawable->draw(mat, stencilValue);
        
        for (auto &child : mChildren)
            child->draw(mat, stencilValue);
        
        removeStencil(projViewParent, stencilValue);
    }
}