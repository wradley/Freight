#include "Conversion.hpp"
#include <Freight/pch.hpp>

namespace fr
{
    Vec2 ToVec2(Real x, Real y)
    {
        return Vec2({x, y});
    }
    
    
    Vec3 ToVec3(Real x, Real y, Real z)
    {
        return Vec3({x, y, z});
    }
    
    
    Vec4 ToVec4(Real x, Real y, Real z, Real w)
    {
        return Vec4({x, y, z, w});
    }


    Vec3 RHCross(const Vec3 &a, const Vec3 &b)
    {
        return Vec3({
            (a.at(1) * b.at(2)) - (a.at(2) * b.at(1)),
            (a.at(2) * b.at(0)) - (a.at(0) * b.at(2)),
            (a.at(0) * b.at(1)) - (a.at(1) * b.at(0))
        });
    }


    Vec2 Normal(const Vec2 &a)
    {
        return a.getNormalized();
    }


    Vec3 Normal(const Vec3 &a)
    {
        return a.getNormalized();
    }


    Vec4 Normal(const Vec4 &a)
    {
        return a.getNormalized();
    }


    Real Len(const Vec2 &a)
    {
        return a.getLength();
    }


    Real Len(const Vec3 &a)
    {
        return a.getLength();
    }


    Real Len(const Vec4 &a)
    {
        return a.getLength();
    }


    Real Dot(const Vec2 &a, const Vec2 &b)
    {
        return a.dot(b);
    }


    Real Dot(const Vec3 &a, const Vec3 &b)
    {
        return a.dot(b);
    }


    Real Dot(const Vec4 &a, const Vec4 &b)
    {
        return a.dot(b);
    }
    
    
    Mat3x3 ToMat3(const Quat &Q)
    {
        Mat3x3 ret;
        Quat q = Q.getNormalized();
        Real qw = q[0];
        Real qx = q[1];
        Real qy = q[2];
        Real qz = q[3];
        Real qx2 = qx * qx;
        Real qy2 = qy * qy;
        Real qz2 = qz * qz;
        
        ret[0][0] = 1 - 2*qy2 - 2*qz2;
        ret[0][1] = 2*qx*qy - 2*qz*qw;
        ret[0][2] = 2*qx*qz + 2*qy*qw;
        
        ret[1][0] = 2*qx*qy + 2*qz*qw;
        ret[1][1] = 1 - 2*qx2 - 2*qz2;
        ret[1][2] = 2*qy*qz - 2*qx*qw;
        
        ret[2][0] = 2*qx*qz - 2*qy*qw;
        ret[2][1] = 2*qy*qz + 2*qx*qw;
        ret[2][2] = 1 - 2*qx2 - 2*qy2;
        
        return ret;
    }
    
    
    Mat4x4 ToMat4(const Quat &Q)
    {
        Mat4x4 ret;
        Quat q = Q.getNormalized();
        Real qw = q[0];
        Real qx = q[1];
        Real qy = q[2];
        Real qz = q[3];
        Real qx2 = qx * qx;
        Real qy2 = qy * qy;
        Real qz2 = qz * qz;
        
        ret[0][0] = 1 - 2*qy2 - 2*qz2;
        ret[0][1] = 2*qx*qy - 2*qz*qw;
        ret[0][2] = 2*qx*qz + 2*qy*qw;
        
        ret[1][0] = 2*qx*qy + 2*qz*qw;
        ret[1][1] = 1 - 2*qx2 - 2*qz2;
        ret[1][2] = 2*qy*qz - 2*qx*qw;
        
        ret[2][0] = 2*qx*qz - 2*qy*qw;
        ret[2][1] = 2*qy*qz + 2*qx*qw;
        ret[2][2] = 1 - 2*qx2 - 2*qy2;
        
        ret[3][3] = 1;
        
        return ret;
    }


    Mat3 Identity3x3()
    {
        Mat3 ret;
        ret[0][0] = (Real)1;
        ret[1][1] = (Real)1;
        ret[2][2] = (Real)1;
        return ret;
    }
    
    
    Mat4x4 Identity4x4()
    {
        Mat4x4 ret;
        ret[0][0] = (Real)1;
        ret[1][1] = (Real)1;
        ret[2][2] = (Real)1;
        ret[3][3] = (Real)1;
        return ret;
    }


    Mat3 SkewSymmetric(const Vec3 &v)
    {
        return Mat3{
            {     0, -v[2],  v[1] },
            {  v[2],     0, -v[0] },
            { -v[1],  v[0],     0 }
        };
    }


    Mat2 Rotate2D(float t)
    {
        return Mat2x2 {
            { cos(t), -sin(t) },
            { sin(t),  cos(t) }
        };
    }

    Mat3 Transform2D(const Vec2 &position, Real orientation, const Vec2 &scale)
    {
        Mat3 p = {
            { 1, 0, (Real)position[0] },
            { 0, 1, (Real)position[1] },
            { 0, 0,                 1 },
        };
        Mat3 r = Rotate2D(orientation);
        r[2][2] = 1;
        Mat3 s{
            { scale[0],        0, 0, },
            {        0, scale[1], 0, },
            {        0,        0, 1  }
        };

        return p * r * s;
    }
    
    
    Mat4x4 Translate(const Vec3 &position)
    {
        Mat4x4 ret = Identity4x4();
        ret[0][3] = position.at(0);
        ret[1][3] = position.at(1);
        ret[2][3] = position.at(2);
        return ret;
    }
    
    
    Mat4x4 Scale(const Vec3 &scale)
    {
        Mat4x4 ret = Identity4x4();
        ret[0][0] = scale.at(0);
        ret[1][1] = scale.at(1);
        ret[2][2] = scale.at(2);
        return ret;
    }


    fr::Real Determinant(const Mat2 &m)
    {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }


    fr::Real Determinant(const Mat3 &m)
    {
        return m[0][0] * m[1][1] * m[2][2] +
               m[0][1] * m[1][2] * m[2][0] +
               m[0][2] * m[1][0] * m[2][1] -
               m[0][2] * m[1][1] * m[2][0] -
               m[0][1] * m[1][0] * m[2][2] -
               m[0][0] * m[1][2] * m[2][1];
    }


    fr::Real Determinant(const Mat4 &m)
    {
        // todo optimze

        auto m0 = m.minor(0, 0);
        auto m1 = m.minor(0, 1);
        auto m2 = m.minor(0, 2);
        auto m3 = m.minor(0, 3);

        auto d0 = Determinant(m0);
        auto d1 = Determinant(m1);
        auto d2 = Determinant(m2);
        auto d3 = Determinant(m3);

        return m.at(0, 0) * Determinant(m.minor(0, 0)) -
               m.at(0, 1) * Determinant(m.minor(0, 1)) +
               m.at(0, 2) * Determinant(m.minor(0, 2)) -
               m.at(0, 3) * Determinant(m.minor(0, 3));
    }


    Mat2 Inverse(const Mat2 &m)
    {
        fr::Real det = Determinant(m);
        if (det == 0.0) return Mat2();

        Mat2 M;
        M[0][0] =  m[1][1] / det;
        M[0][1] = -m[0][1] / det;
        M[1][0] = -m[1][0] / det;
        M[1][1] =  m[0][0] / det;

        return M;
    }


    Mat3 Inverse(const Mat3 &m)
    {
        fr::Real det = Determinant(m);
        if (det == 0.0) return Mat3();

        auto a = m[0][0];
        auto b = m[0][1];
        auto c = m[0][2];
        auto d = m[1][0];
        auto e = m[1][1];
        auto f = m[1][2];
        auto g = m[2][0];
        auto h = m[2][1];
        auto i = m[2][2];

        Mat3 M;
        M[0][0] = ((e * i) - (f * h)) / det;
        M[0][1] = ((h * c) - (i * b)) / det;
        M[0][2] = ((b * f) - (c * e)) / det;
        M[1][0] = ((g * f) - (d * i)) / det;
        M[1][1] = ((a * i) - (g * c)) / det;
        M[1][2] = ((d * c) - (a * f)) / det;
        M[2][0] = ((d * h) - (g * e)) / det;
        M[2][1] = ((g * b) - (a * h)) / det;
        M[2][2] = ((a * e) - (d * b)) / det;

        return M;
    }


    Mat4 Inverse(const Mat4 &m_)
    {
        fr::Real det = Determinant(m_);
        if (det == 0.0) return Mat4();

        auto a = m_[0][0];
        auto b = m_[0][1];
        auto c = m_[0][2];
        auto d = m_[0][3];
        auto e = m_[1][0];
        auto f = m_[1][1];
        auto g = m_[1][2];
        auto h = m_[1][3];
        auto i = m_[2][0];
        auto j = m_[2][1];
        auto k = m_[2][2];
        auto l = m_[2][3];
        auto m = m_[3][0];
        auto n = m_[3][1];
        auto o = m_[3][2];
        auto p = m_[3][3];

        Mat4 M;
        M[0][0] = (-(h*k*n) + (g*l*n) + (h*j*o) - (f*l*o) - (g*j*p) + (f*k*p)) / det;
        M[0][1] = ( (d*k*n) - (c*l*n) - (d*j*o) + (b*l*o) + (c*j*p) - (b*k*p)) / det;
        M[0][2] = (-(d*g*n) + (c*h*n) + (d*f*o) - (b*h*o) - (c*f*p) + (b*g*p)) / det;
        M[0][3] = ( (d*g*j) - (c*h*j) - (d*f*k) + (b*h*k) + (c*f*l) - (b*g*l)) / det;
        M[1][0] = ( (h*k*m) - (g*l*m) - (h*i*o) + (e*l*o) + (g*i*p) - (e*k*p)) / det;
        M[1][1] = (-(d*k*m) + (c*l*m) + (d*i*o) - (a*l*o) - (c*i*p) + (a*k*p)) / det;
        M[1][2] = ( (d*g*m) - (c*h*m) - (d*e*o) + (a*h*o) + (c*e*p) - (a*g*p)) / det;
        M[1][3] = (-(d*g*i) + (c*h*i) + (d*e*k) - (a*h*k) - (c*e*l) + (a*g*l)) / det;
        M[2][0] = (-(h*j*m) + (f*l*m) + (h*i*n) - (e*l*n) - (f*i*p) + (e*j*p)) / det;
        M[2][1] = ( (d*j*m) - (b*l*m) - (d*i*n) + (a*l*n) + (b*i*p) - (a*j*p)) / det;
        M[2][2] = (-(d*f*m) + (b*h*m) + (d*e*n) - (a*h*n) - (b*e*p) + (a*f*p)) / det;
        M[2][3] = ( (d*f*i) - (b*h*i) - (d*e*j) + (a*h*j) + (b*e*l) - (a*f*l)) / det;
        M[3][0] = ( (g*j*m) - (f*k*m) - (g*i*n) + (e*k*n) + (f*i*o) - (e*j*o)) / det;
        M[3][1] = (-(c*j*m) + (b*k*m) + (c*i*n) - (a*k*n) - (b*i*o) + (a*j*o)) / det;
        M[3][2] = ( (c*f*m) - (b*g*m) - (c*e*n) + (a*g*n) + (b*e*o) - (a*f*o)) / det;
        M[3][3] = (-(c*f*i) + (b*g*i) + (c*e*j) - (a*g*j) - (b*e*k) + (a*f*k)) / det;

        return M;
    }


    Mat4 RHPerspectiveMatrix(Real n, Real f, Real fov, Real ar)
    {
        Real tf = tan(fov / (Real)2);

        Real m00 = (Real)1 / (ar * tf);
        Real m11 = (Real)1 / tf;
        Real m22 = (-n - f) / (f - n);
        Real m23 = -((Real)2 * f * n) / (f - n);

        return Mat4({
            {m00,   0,   0,   0},
            {  0, m11,   0,   0},
            {  0,   0, m22, m23},
            {  0,   0,  -1,   0},
        });
    }


    Mat4 RHLookAtMatrix(const Vec3 &eye, const Vec3 &target, const Vec3 &up)
    {
        /*Vec3 z = Normal(eye - target);
        Vec3 x = Normal(RHCross(up, z));
        Vec3 y = RHCross(z, x);

        return Mat4({
            {x[0], x[1], x[2], Dot(x, eye)},
            {y[0], y[1], y[2], Dot(y, eye)},
            {z[0], z[1], z[2], -Dot(z, eye)},
            {   0,    0,    0,           1}
        });*/

        Vec3 z = Normal(target - eye);
        Vec3 x = Normal(RHCross(z, up));
        Vec3 y = RHCross(x, z);

        return Mat4({
            { x[0],  x[1],  x[2], -Dot(x, eye)},
            { y[0],  y[1],  y[2], -Dot(y, eye)},
            {-z[0], -z[1], -z[2],  Dot(z, eye)},
            {    0,     0,     0,            1}
        });
    }


    Mat3 Ortho2D(Real width, Real height)
    {
        return Mat3{
            { (Real)2 / width,                 0, 0 },
            {               0, -(Real)2 / height, 0 },
            {               0,                 0, 1 }
        };
    }
    
    
    Quat AxisAngleToQuat(const Vec3 &a, Real angle)
    {
        Real ha = angle / (Real)2;
        Real sha = sin(ha);

        return Quat({
            cos(ha),        // w
            a.at(0) * sha,  // x
            a.at(1) * sha,  // y
            a.at(2) * sha   // z
        }).getNormalized();
    }


    Quat ToQuat(Real w, Real x, Real y, Real z)
    {
        return Quat({w, x, y, z});
    }
    
    
    Quat ToQuat(const Mat3x3 &m)
    {
        Real qw;
        Real qx;
        Real qy;
        Real qz;

        Real m00 = m[0][0];
        Real m01 = m[0][1];
        Real m02 = m[0][2];
        Real m10 = m[1][0];
        Real m11 = m[1][1];
        Real m12 = m[1][2];
        Real m20 = m[2][0];
        Real m21 = m[2][1];
        Real m22 = m[2][2];

        Real tr = m00 + m11 + m22;

        if (tr > 0) {
            Real S = sqrt(tr + (Real)1) * (Real)2;
            qw = (Real)0.25 * S;
            qx = (m21 - m12) / S;
            qy = (m02 - m20) / S;
            qz = (m10 - m01) / S;
        }
        else if ((m00 > m11) &(m00 > m22)) {
            Real S = sqrt((Real)1 + m00 - m11 - m22) * (Real)2;
            qw = (m21 - m12) / S;
            qx = (Real)0.25 * S;
            qy = (m01 + m10) / S;
            qz = (m02 + m20) / S;
        }
        else if (m11 > m22) {
            Real S = sqrt((Real)1 + m11 - m00 - m22) * (Real)2;
            qw = (m02 - m20) / S;
            qx = (m01 + m10) / S;
            qy = (Real)0.25 * S;
            qz = (m12 + m21) / S;
        }
        else {
            Real S = sqrt((Real)1 + m22 - m00 - m11) * (Real)2;
            qw = (m10 - m01) / S;
            qx = (m02 + m20) / S;
            qy = (m12 + m21) / S;
            qz = (Real)0.25 * S;
        }

        return Quat({qw, qx, qy, qz});
    }
    
    
    Quat ToQuat(const Mat4x4 &m)
    {
        Real qw;
        Real qx;
        Real qy;
        Real qz;
        
        Real m00 = m[0][0];
        Real m01 = m[0][1];
        Real m02 = m[0][2];
        Real m10 = m[1][0];
        Real m11 = m[1][1];
        Real m12 = m[1][2];
        Real m20 = m[2][0];
        Real m21 = m[2][1];
        Real m22 = m[2][2];
        
        Real tr = m00 + m11 + m22;
        
        if (tr > 0) {
            Real S = sqrt(tr+(Real)1) * (Real)2;
            qw = (Real)0.25 * S;
            qx = (m21 - m12) / S;
            qy = (m02 - m20) / S;
            qz = (m10 - m01) / S;
        } else if ((m00 > m11)&(m00 > m22)) {
            Real S = sqrt((Real)1 + m00 - m11 - m22) * (Real)2;
            qw = (m21 - m12) / S;
            qx = (Real)0.25 * S;
            qy = (m01 + m10) / S;
            qz = (m02 + m20) / S;
        } else if (m11 > m22) {
            Real S = sqrt((Real)1 + m11 - m00 - m22) * (Real)2;
            qw = (m02 - m20) / S;
            qx = (m01 + m10) / S;
            qy = (Real)0.25 * S;
            qz = (m12 + m21) / S;
        } else {
            Real S = sqrt((Real)1 + m22 - m00 - m11) * (Real)2;
            qw = (m10 - m01) / S;
            qx = (m02 + m20) / S;
            qy = (m12 + m21) / S;
            qz = (Real)0.25 * S;
        }
        
        return Quat({qw, qx, qy, qz});
    }
}
