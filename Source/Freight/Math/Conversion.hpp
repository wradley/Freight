#pragma once
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

namespace fr
{
    inline bool Eql(fr::f32 a, fr::f32 b, fr::f32 epsilon = std::numeric_limits<fr::f32>::epsilon()) {
        return std::abs(a - b) < epsilon;
    }

    inline bool Eql(fr::f64 a, fr::f64 b, fr::f64 epsilon = std::numeric_limits<fr::f64>::epsilon()) {
        return std::abs(a - b) < epsilon;
    }

    template <class T, unsigned int N>
    inline bool Eql(const Vector<T, N> &a, const Vector<T, N> &b, T epsilon = std::numeric_limits<T>::epsilon()) {
        for (unsigned int i = 0; i < N; ++i) {
            if (std::abs(a[i] - b[i]) >= epsilon)
                return false;
        }
        return true;
    }

    template <class T, unsigned int M, unsigned int N>
    inline bool Eql(const Matrix<T, M, N> &a, const Matrix<T, M, N> &b, T epsilon = std::numeric_limits<T>::epsilon()) {
        for (unsigned int i = 0; i < M; ++i) {
            for (unsigned int j = 0; j < N; ++j) {
                if (std::abs(a[i][j] - b[i][j]) >= epsilon)
                    return false;
            }
        }
        return true;
    }

    template <class T>
    inline bool Eql(const Quaternion<T> &a, const Quaternion<T> &b, T epsilon = std::numeric_limits<T>::epsilon()) {
        for (unsigned int i = 0; i < 4; ++i) {
            if (std::abs(a[i] - b[i]) >= epsilon)
                return false;
        }
        return true;
    }

    Vec2 ToVec2(Real x, Real y);
    Vec3 ToVec3(Real x, Real y, Real z);
    Vec4 ToVec4(Real x, Real y, Real z, Real w);
    Vec3 RHCross(const Vec3 &a, const Vec3 &b);
    Vec2 Normal(const Vec2 &a);
    Vec3 Normal(const Vec3 &a);
    Vec4 Normal(const Vec4 &a);
    Real Len(const Vec2 &a);
    Real Len(const Vec3 &a);
    Real Len(const Vec4 &a);
    Real Dot(const Vec2 &a, const Vec2 &b);
    Real Dot(const Vec3 &a, const Vec3 &b);
    Real Dot(const Vec4 &a, const Vec4 &b);
    
    Mat3 ToMat3(const Quat &q);
    Mat4 ToMat4(const Quat &q);
    Mat3 Identity3x3();
    Mat4 Identity4x4();
    // equivalent to vector cross product where Cross(v, a) = V_skew * a
    Mat3 SkewSymmetric(const Vec3 &v);
    Mat2 Rotate2D(float rads);
    Mat3 Transform2D(const Vec2 &position, Real orientation, const Vec2 &scale);
    Mat4 Translate(const Vec3 &position);
    Mat4 Scale(const Vec3 &scale);
    fr::Real Determinant(const Mat2 &m);
    fr::Real Determinant(const Mat3 &m);
    fr::Real Determinant(const Mat4 &m);
    Mat2 Inverse(const Mat2 &m);
    Mat3 Inverse(const Mat3 &m);
    Mat4 Inverse(const Mat4 &m);
    template <class T, unsigned int M, unsigned int N>
    inline Matrix<T, N, M> Transpose(const Matrix<T, M, N> &m) { return m.transpose(); }
    Mat4 RHPerspectiveMatrix(Real nearPlane, Real farPlane, Real fovInRadians, Real aspectRatio);
    Mat4 RHLookAtMatrix(const Vec3 &eye, const Vec3 &target, const Vec3 &up);

    // Calculate orthographic matrix for a screen starting at 0, 0 and dimensions of width, height.
    Mat3 Ortho2D(Real width, Real height);
    
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
