#pragma once
#include "../../Include/Freight/pch.hpp"
#include "../../Include/Freight/Math.hpp"

namespace fr::gfx
{
    class Drawable2D;
    class Camera2D;

    class Node2D
    {
        std::vector<Node2D*> mChildren;
        std::vector<Drawable2D*> mDrawables;
        std::vector<Camera2D*> mCameras;
        
        Vec2 mPosition;
        Real mOrientation;
        Vec2 mScale;
        Vec2 mCrop; // negative means no crop

    public:
        
        Node2D();
        ~Node2D();
        
        Vec2 getPosition() const;
        void setPosition(const Vec2 &p);
        
        Real getOrientation() const;
        void setOrientation(Real o);
        
        Vec2 getScale() const;
        void setScale(const Vec2 &s);
        
        Vec2 getCrop() const;
        void setCrop(const Vec2 &c);
        void setNoCrop();
        
    private:
        
        void draw(const Mat3 &projViewParent, u8 stencilValue);
        void drawStencil(const Mat3 &transform, u8 stencilValue);
        void removeStencil(const Mat3 &transform, u8 stencilValue);
        void getLocalMatrix(Mat3 &out);
        
    };
}