#pragma once
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

namespace FR8
{
    Vec2 ToVec2(Real x, Real y);
    Vec3 ToVec3(Real x, Real y, Real z);
    Vec4 ToVec4(Real x, Real y, Real z, Real w);
    
    Mat3x3 ToMat3x3(const Quat &q);
    Mat4x4 ToMat4x4(const Quat &q);
    Mat4x4 Identity4x4();
    Mat4x4 Translate(const Vec3 &position);
    Mat4x4 Scale(const Vec3 &scale);
    
    Quat ToQuat(Real w, Real x, Real y, Real z);
    Quat ToQuat(const Mat3x3 &m);
    Quat ToQuat(const Mat4x4 &m);
}
