#pragma once
#include <iostream>
#include <cmath>
#include <initializer_list>
#include "Precision.hpp"

namespace fr
{
    template <class T, unsigned int N>
    class Vector
    {
    public:
        
        Vector(T s = (T)0) : mData{} {
            //for (unsigned int i = 0; i < N; ++i)
            //    mData[i] = (T) s;
        }
        
        
        Vector(const Vector &v) {
            for (unsigned int i = 0; i < N; ++i)
                mData[i] = v.mData[i];
        }
        
        
        Vector& operator= (const Vector &v) {
            for (unsigned int i = 0; i < N; ++i)
                mData[i] = v.mData[i];
            return *this;
        }

        
        template <class Tt, unsigned int Nn>
        Vector(const Vector<Tt, Nn> &v) {
            for (unsigned int i = 0; i < N; ++i) {
                if (i >= Nn) mData[i] = 0;
                else mData[i] = (T)v.mData[i];
            }
        }
        
        
        template <class Tt, unsigned int Nn>
        Vector& operator= (const Vector<Tt, Nn> &v) = delete;
        
        
        Vector(const T (&s)[N]) {
            for (unsigned int i = 0; i < N; ++i) {
                mData[i] = s[i];
            }
        }


        Vector(std::initializer_list<T> list) {
            int i = 0;
            for (auto it = std::begin(list); it != std::end(list); ++it, ++i) {
                if (i == N) break;
                mData[i] = *it;
            }
        }
        
        
        Vector& operator= (const T (&s)[N]) {
            for (unsigned int i = 0; i < N; ++i) {
                mData[i] = s[i];
            }
            return *this;
        }
        
        
        Vector operator+ (const Vector &v) const {
            Vector ret;
            for (unsigned int i = 0; i < N; ++i)
                ret.mData[i] = mData[i] + v.mData[i];
            return ret;
        }
        
        
        Vector operator- (const Vector &v) const {
            Vector ret;
            for (unsigned int i = 0; i < N; ++i)
                ret.mData[i] = mData[i] - v.mData[i];
            return ret;
        }
        
        
        Vector operator* (T s) const {
            Vector ret;
            for (unsigned int i = 0; i < N; ++i)
                ret.mData[i] = mData[i] * s;
            return ret;
        }
        
        
        Vector operator/ (T s) const {
            Vector ret;
            for (unsigned int i = 0; i < N; ++i)
                ret.mData[i] = mData[i] / s;
            return ret;
        }
        
        
        Vector& operator+= (const Vector &v) {
            for (unsigned int i = 0; i < N; ++i)
                mData[i] += v.mData[i];
            return *this;
        }
        
        
        Vector& operator-= (const Vector &v) {
            for (unsigned int i = 0; i < N; ++i)
                mData[i] -= v.mData[i];
            return *this;
        }
        
        
        Vector& operator*= (T s) {
            for (unsigned int i = 0; i < N; ++i)
                mData[i] *= s;
            return *this;
        }
        
        
        Vector& operator/= (T s) {
            for (unsigned int i = 0; i < N; ++i)
                mData[i] /= s;
            return *this;
        }
        
        
        T getLength() const {
            T sum = (T) 0;
            for (unsigned int i = 0; i < N; ++i)
                sum += mData[i] * mData[i];
            return sqrt(sum);
        }
        
        
        Vector getNormalized() const {
            return *this / getLength();
        }
        
        
        Vector& normalize() {
            *this /= getLength();
            return *this;
        }
        
        
        T dot(const Vector &v) const {
            T total = (T) 0;
            for (unsigned int i = 0; i < N; ++i) {
                total += mData[i] * v.mData[i];
            }
            return total;
        }
        
        
        T& operator[] (unsigned int i) {
            return mData[i];
        }
        
        
        T at(unsigned int i) const {
            return mData[i];
        }
        
        
        friend std::ostream& operator<< (std::ostream &out, const Vector &v) {
            out << "{";
            for (unsigned int i = 0; i < N; ++i) {
                out << v.mData[i];
                if (i < N-1) out << ", ";
            }
            out << "}";
            return out;
        }
        
    public:
        
        T mData[N];
        
    };
    
    
    typedef Vector<float, 2> Flt2;
    typedef Vector<float, 3> Flt3;
    typedef Vector<float, 4> Flt4;
    
    typedef Vector<double, 2> Dbl2;
    typedef Vector<double, 3> Dbl3;
    typedef Vector<double, 4> Dbl4;
    
    typedef Vector<Real, 2> Vec2;
    typedef Vector<Real, 3> Vec3;
    typedef Vector<Real, 4> Vec4;
}
