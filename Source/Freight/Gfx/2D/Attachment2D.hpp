#pragma once
#include "../../Math/Matrix.hpp"

namespace fr::gfx
{
    class Attachment2D
    {
        Vec2 mCenter;
        Real mOrientation;
        Vec2 mSize;

    public:

        Attachment2D();
        virtual ~Attachment2D();

        Vec2 getCenter() const;
        void setCenter(const Vec2 &p);
        
        Real getOrientation() const;
        void setOrientation(Real o);
        
        Vec2 getSize() const;
        void setSize(const Vec2 &s);

        void getLocalTransform(Mat3 &out) const;

    };

    class Drawable2D : public Attachment2D
    {
        i32 mLayer;

        friend class Node2D;
        virtual void draw(const Mat3 &projView) = 0;
        
    public:

        Drawable2D();
        virtual ~Drawable2D();

        i32 getLayer() const;
        void setLayer(i32 layer);

    };
}