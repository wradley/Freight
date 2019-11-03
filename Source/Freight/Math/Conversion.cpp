#include "Conversion.hpp"

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
    
    
    Mat4x4 Identity4x4()
    {
        Mat4x4 ret;
        ret[0][0] = (Real)1;
        ret[1][1] = (Real)1;
        ret[2][2] = (Real)1;
        ret[3][3] = (Real)1;
        return ret;
    }


    Mat2x2 Rotate2D(float t)
    {
        return Mat2x2 {
            cos(t), -sin(t),
            sin(t),  cos(t)
        };
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
        Quat ret;
        Real qw = ret[0];
        Real qx = ret[1];
        Real qy = ret[2];
        Real qz = ret[3];
        
        Real m00 = m.at(0, 0);
        Real m01 = m.at(0, 1);
        Real m02 = m.at(0, 1);
        Real m10 = m.at(1, 0);
        Real m11 = m.at(1, 1);
        Real m12 = m.at(1, 1);
        Real m20 = m.at(2, 0);
        Real m21 = m.at(2, 1);
        Real m22 = m.at(2, 1);
        
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
        
        return ret;
    }
    
    
    Quat ToQuat(const Mat4x4 &m)
    {
        Quat ret;
        Real qw = ret[0];
        Real qx = ret[1];
        Real qy = ret[2];
        Real qz = ret[3];
        
        Real m00 = m.at(0, 0);
        Real m01 = m.at(0, 1);
        Real m02 = m.at(0, 1);
        Real m10 = m.at(1, 0);
        Real m11 = m.at(1, 1);
        Real m12 = m.at(1, 1);
        Real m20 = m.at(2, 0);
        Real m21 = m.at(2, 1);
        Real m22 = m.at(2, 1);
        
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
        
        return ret;
    }
}
