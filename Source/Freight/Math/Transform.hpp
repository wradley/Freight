#pragma once
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

namespace fr
{
    class Transform
    {
    public:
        
        Transform();
        Transform(const Transform &t);
        Transform& operator= (const Transform &t);
        ~Transform();
        
        Mat4x4 getMat() const;
        Vec3 getForward() const;

    public:
        
        Vec3 position;
        Quat rotation;
        Vec3 scale;
        
    };
}
