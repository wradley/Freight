#pragma once
#include "../../Math/Matrix.hpp"
#include "Attachment2D.hpp"

namespace fr::gfx
{
    class Camera2D : public Attachment2D
    {
    public:

        Camera2D();
        ~Camera2D();
        
        void getViewMat(uint fbWidth, uint fbHeight, Mat3 &out);
    };
}