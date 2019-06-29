#include "Conversion.hpp"

namespace FR8
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
    
    
    Mat3x3 ToMat3x3(const Quat &Q)
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
    
    
    Mat4x4 ToMat4x4(const Quat &Q)
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
            Real S = sqrt(tr+1.0) * 2;
            qw = 0.25 * S;
            qx = (m21 - m12) / S;
            qy = (m02 - m20) / S;
            qz = (m10 - m01) / S;
        } else if ((m00 > m11)&(m00 > m22)) {
            Real S = sqrt(1.0 + m00 - m11 - m22) * 2;
            qw = (m21 - m12) / S;
            qx = 0.25 * S;
            qy = (m01 + m10) / S;
            qz = (m02 + m20) / S;
        } else if (m11 > m22) {
            Real S = sqrt(1.0 + m11 - m00 - m22) * 2;
            qw = (m02 - m20) / S;
            qx = (m01 + m10) / S;
            qy = 0.25 * S;
            qz = (m12 + m21) / S;
        } else {
            Real S = sqrt(1.0 + m22 - m00 - m11) * 2;
            qw = (m10 - m01) / S;
            qx = (m02 + m20) / S;
            qy = (m12 + m21) / S;
            qz = 0.25 * S;
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
            Real S = sqrt(tr+1.0) * 2;
            qw = 0.25 * S;
            qx = (m21 - m12) / S;
            qy = (m02 - m20) / S;
            qz = (m10 - m01) / S;
        } else if ((m00 > m11)&(m00 > m22)) {
            Real S = sqrt(1.0 + m00 - m11 - m22) * 2;
            qw = (m21 - m12) / S;
            qx = 0.25 * S;
            qy = (m01 + m10) / S;
            qz = (m02 + m20) / S;
        } else if (m11 > m22) {
            Real S = sqrt(1.0 + m11 - m00 - m22) * 2;
            qw = (m02 - m20) / S;
            qx = (m01 + m10) / S;
            qy = 0.25 * S;
            qz = (m12 + m21) / S;
        } else {
            Real S = sqrt(1.0 + m22 - m00 - m11) * 2;
            qw = (m10 - m01) / S;
            qx = (m02 + m20) / S;
            qy = (m12 + m21) / S;
            qz = 0.25 * S;
        }
        
        return ret;
    }
}
