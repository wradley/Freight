#include "Transform.hpp"
#include "Conversion.hpp"

namespace FR8
{
    Transform::Transform() :
        position({0,0,0}),
        rotation({1,0,0,0}),
        scale({1,1,1})
    {}
    
    
    Transform::Transform(const Transform &t) :
        position(t.position),
        rotation(t.rotation),
        scale(t.scale)
    {}
    
    
    Transform& Transform::operator= (const Transform &t)
    {
        position = t.position;
        rotation = t.rotation;
        scale = t.scale;
        return *this;
    }
    
    
    Transform::~Transform()
    {}
    
    
    Mat4x4 Transform::getMat() const
    {
        Mat4x4 t = Translate(position);
        Mat4x4 r = ToMat4x4(rotation);
        Mat4x4 s = Scale(scale);
        return t * r * s;
    }
}
