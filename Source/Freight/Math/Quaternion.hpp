#pragma once
#include <iostream>
#include <cmath>
#include <initializer_list>
#include "../Defines.hpp"

namespace fr
{
    // stored in the order: w, x, y, z  ~>  (a + bi + cj + dk)
    template <class T>
    class Quaternion
    {
    public:
        
        
        Quaternion() {
            mData[0] = (T) 1;
            mData[1] = (T) 0;
            mData[2] = (T) 0;
            mData[3] = (T) 0;
        }
        
        
        Quaternion(const T (&t)[4]) {
            mData[0] = t[0];
            mData[1] = t[1];
            mData[2] = t[2];
            mData[3] = t[3];
        }
        

        Quaternion(std::initializer_list<T> list) : mData{0} {
            int i = 0;
            for (auto it = std::begin(list); it != std::end(list); ++it, ++i) {
                if (i == 4) break; // if init list is too long, break
                mData[i] = *it;
            }
        }
        
        
        Quaternion(const Quaternion &q) {
            mData[0] = q.mData[0];
            mData[1] = q.mData[1];
            mData[2] = q.mData[2];
            mData[3] = q.mData[3];
        }
        
        
        Quaternion& operator= (const Quaternion &q) {
            mData[0] = q.mData[0];
            mData[1] = q.mData[1];
            mData[2] = q.mData[2];
            mData[3] = q.mData[3];
            return *this;
        }
        
        
        template <class Tt>
        Quaternion(const Quaternion<Tt> &q) {
            mData[0] = (T) q.mData[0];
            mData[1] = (T) q.mData[1];
            mData[2] = (T) q.mData[2];
            mData[3] = (T) q.mData[3];
        }
        

        template <class Tt>
        Quaternion& operator= (const Quaternion<Tt> &q) = delete;
        
        
        ~Quaternion() {}


        Quaternion& operator*= (const Quaternion &b) {
            Quaternion other{(*this) * b};
            *this = other;
            return *this;
        }
        
        
        Quaternion operator* (const Quaternion &b) const {
            Quaternion ret;

            const T *q1 = mData;
            const T *q2 = b.mData;
            T *q3 = ret.mData;
            
            q3[0] = q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2] - q1[3]*q2[3];
            q3[1] = q1[0]*q2[1] + q1[1]*q2[0] + q1[2]*q2[3] - q1[3]*q2[2];
            q3[2] = q1[0]*q2[2] - q1[1]*q2[3] + q1[2]*q2[0] + q1[3]*q2[1];
            q3[3] = q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1] + q1[3]*q2[0];
            
            return ret;
        }


        Vector<T, 3> operator* (const Vector<T, 3> &v) const {
            const Quaternion &r1(*this);
            const Quaternion r2({r1[0], -r1[1], -r1[2], -r1[3]});
            const Quaternion p({0, v.at(0), v.at(1), v.at(2)});
            Quaternion result = r1 * p * r2;
            return Vector<T, 3>({result[1], result[2], result[3]});
        }


        // todo: inaccurate for large rotations
        Quaternion& operator+= (const Vector<T, 3> &v) {
            Quaternion q({
                0,
                v[0],
                v[1],
                v[2]
            });
            q *= *this;
            mData[0] += q[0] * (fr::Real)0.5;
            mData[1] += q[1] * (fr::Real)0.5;
            mData[2] += q[2] * (fr::Real)0.5;
            mData[3] += q[3] * (fr::Real)0.5;
            return *this;
        }


        Quaternion operator+ (const Vector<T, 3> &v) const {
            Quaternion q(*this);
            return q += v;
        }
        
        
        T getLength() const {
            return sqrt(mData[0]*mData[0] + mData[1]*mData[1] + mData[2]*mData[2] + mData[3]*mData[3]);
        }
        
        
        Quaternion getNormalized() const {
            Quaternion q;
            T length = getLength();
            q.mData[0] = mData[0] / length;
            q.mData[1] = mData[1] / length;
            q.mData[2] = mData[2] / length;
            q.mData[3] = mData[3] / length;
            return q;
        }
        
        
        Quaternion& normalize() {
            T length = getLength();
            mData[0] = mData[0] / length;
            mData[1] = mData[1] / length;
            mData[2] = mData[2] / length;
            mData[3] = mData[3] / length;
            return *this;
        }
        
        
        T& operator[] (unsigned int i) {
            return mData[i];
        }


        const T operator[] (unsigned int i) const {
            return mData[i];
        }
        
        
        friend std::ostream& operator<< (std::ostream &out, const Quaternion &q) {
            out << "{" << q.mData[0] << ", " << q.mData[1] << ", " << q.mData[2] << ", " << q.mData[3] << "}";
            return out;
        }
        
    public:
        
        T mData[4];
        
    };
    
    
    typedef Quaternion<float>  FltQuat;
    typedef Quaternion<double> DblQuat;
    typedef Quaternion<Real> Quat;
}
