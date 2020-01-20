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
    Vec2 Normal(const Vec2 &a);
    Vec3 Normal(const Vec3 &a);
    Vec4 Normal(const Vec4 &a);
    Real Dot(const Vec2 &a, const Vec2 &b);
    Real Dot(const Vec3 &a, const Vec3 &b);
    Real Dot(const Vec4 &a, const Vec4 &b);
    
    Mat3 ToMat3(const Quat &q);
    Mat4 ToMat4(const Quat &q);
    Mat4 Identity4x4();
    Mat2 Rotate2D(float t);
    Mat4 Translate(const Vec3 &position);
    Mat4 Scale(const Vec3 &scale);
    fr::Real Determinant(const Mat2 &m);
    fr::Real Determinant(const Mat3 &m);
    fr::Real Determinant(const Mat4 &m);
    Mat2 Inverse(const Mat2 &m);
    Mat3 Inverse(const Mat3 &m);
    Mat4 Inverse(const Mat4 &m);
    Mat4 RHPerspectiveMatrix(Real nearPlane, Real farPlane, Real fovInRadians, Real aspectRatio);
    Mat4 RHLookAtMatrix(const Vec3 &eye, const Vec3 &target, const Vec3 &up);
    
    Quat AxisAngleToQuat(const Vec3 &axis, Real angleInRadians);
    Quat ToQuat(Real w, Real x, Real y, Real z);
    Quat ToQuat(const Mat3x3 &m);
    Quat ToQuat(const Mat4x4 &m);

    inline Real ToRad(Real degrees) { 
        return degrees * (PI / (Real)180);
    }

    inline Real ToDeg(Real radians) {
        return radians * ((Real)180 / PI); 
    }
}
