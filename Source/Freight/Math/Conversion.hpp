#pragma once
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

namespace fr
{
    Vec2 ToVec2(Real x, Real y);
    Vec3 ToVec3(Real x, Real y, Real z);
    Vec4 ToVec4(Real x, Real y, Real z, Real w);
    Vec3 RHCross(const Vec3 &a, const Vec3 &b);
    
    Mat3 ToMat3x3(const Quat &q);
    Mat4 ToMat4x4(const Quat &q);
    Mat4 Identity4x4();
    Mat2 Rotate2D(float t);
    Mat4 Translate(const Vec3 &position);
    Mat4 Scale(const Vec3 &scale);
    Mat4 RHProjectionMatrix(Real far, Real near, Real fovInRadians, Real aspectRatio);
    Mat4 RHLookAtMatrix(const Vec3 &eye, const Vec3 &target, const Vec3 &up);
    
    Quat ToQuat(Real w, Real x, Real y, Real z);
    Quat ToQuat(const Mat3x3 &m);
    Quat ToQuat(const Mat4x4 &m);

    inline Real ToRad(Real degrees) { return PI / (Real)180; }
    inline Real ToDeg(Real degrees) { return (Real)180 / PI; }
}
