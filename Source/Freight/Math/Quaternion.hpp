#pragma once
#include <iostream>
#include <cmath>
#include "Matrix.hpp"
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
        
        
        Quaternion& operator= (const T (&t)[4]) {
            mData[0] = t[0];
            mData[1] = t[1];
            mData[2] = t[2];
            mData[3] = t[3];
            return *this;
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
        
        
        Quaternion operator* (const Quaternion &b) const {
            Quaternion ret;
            //T (&q1)[] = mData;
            //T (&q2)[] = b.mData;
            //T (&q3)[] = ret.mData;
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
            const Quaternion r2({r1.at(0), -r1.at(1), -r1.at(2), -r1.at(3)});
            const Quaternion p({0, v.at(0), v.at(1), v.at(2)});
            Quaternion result = r1 * p * r2;
            return Vector<T, 3>({result[1], result[2], result[3]});
        }


        T at(size_t index) const {
            return mData[index];
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
