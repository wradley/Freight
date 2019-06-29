#pragma once
#include <iostream>
#include "Vector.hpp"
#include "Precision.hpp"

namespace FR8
{
    template <class T, unsigned int M, unsigned int N>
    class Matrix
    {
    public:
        
        
        Matrix() {}
        
        
        Matrix(const T (&v)[M][N]) {
            for (unsigned int i = 0; i < M; ++i) {
                mRows[i] = Vector<T, N>(v[i]);
            }
        }
        
        
        Matrix& operator= (const T (&v)[M][N]) {
            for (unsigned int i = 0; i < M; ++i) {
                mRows[i] = Vector<T, N>(v[i]);
            }
            return *this;
        }
        
        
        Matrix(const Matrix &m) {
            for (unsigned int i = 0; i < M; ++i)
                mRows[i] = m.mRows[i];
        }
        
        
        Matrix& operator= (const Matrix &m) {
            for (unsigned int i = 0; i < M; ++i)
                mRows[i] = m.mRows[i];
            return *this;
        }
        
        
        template <class Tt, unsigned int Mm, unsigned int Nn>
        Matrix(const Matrix<Tt, Mm, Nn> &m) {
            for (unsigned int i = 0; i < M; ++i) {
                if (i >= Mm) mRows[i] = Vector<T, N>();
                else mRows[i] = Vector<T, N>(m.mRows[i]);
            }
        }
        
        
//        template <class Tt, unsigned int Mm, unsigned int Nn>
//        Matrix& operator= (const Matrix<Tt, Mm, Nn> &m) {
//            for (unsigned int i = 0; i < M; ++i) {
//                if (i >= Mm) mRows[i] = Vector<T, N>();
//                else mRows[i] = m.mRows[i];
//            }
//            return *this;
//        }
        
        
        template <class Tt, unsigned int Mm, unsigned int Nn>
        Matrix& operator= (const Matrix<Tt, Mm, Nn> &m) = delete;
        
        
        ~Matrix() {}
        
        
        template <unsigned int Q>
        Matrix<T, M, Q> operator* (const Matrix<T, N, Q> &other) const {
            Matrix<T, M, Q> ret;
            for (unsigned int m = 0; m < M; ++m) {
                for (unsigned int q = 0; q < Q; ++q) {
                    for (unsigned int n = 0; n < N; ++n) {
                        ret[m][q] += at(m,n) * other.at(n, q);
                    }
                }
            }
            return ret;
        }
        
        
        Matrix operator* (T s) const {
            Matrix ret;
            for (unsigned int i = 0; i < M; ++i)
                ret.mRows[i] = mRows[i] * s;
            return ret;
        }
        
        
        Matrix operator/ (T s) const {
            Matrix ret;
            for (unsigned int i = 0; i < M; ++i)
                ret.mRows[i] = mRows[i] / s;
            return ret;
        }
        
        
        Matrix& operator*= (T s) {
            for (unsigned int i = 0; i < M; ++i)
                mRows[i] *= s;
            return *this;
        }
        
        
        Matrix& operator/= (T s) {
            for (unsigned int i = 0; i < M; ++i)
                mRows[i] /= s;
            return *this;
        }
        
        
        Vector<T, N>& operator[] (unsigned int i) {
            return mRows[i];
        }
        
        
        T at(unsigned int i, unsigned int j) const {
            return mRows[i].at(j);
        }
        
        
        friend std::ostream& operator<< (std::ostream &out, const Matrix &m) {
            for (unsigned int i = 0; i < M; ++i) {
                out << m.mRows[i];
                if (i < M-1) out << '\n';
            }
            return out;
        }
        
        
    public:
        
        Vector<T, N> mRows[M];
        
    };
    
    
    typedef Matrix<float, 2, 2> Flt2x2;
    typedef Matrix<float, 2, 3> Flt2x3;
    typedef Matrix<float, 2, 4> Flt2x4;
    
    typedef Matrix<float, 3, 2> Flt3x2;
    typedef Matrix<float, 3, 3> Flt3x3;
    typedef Matrix<float, 3, 4> Flt3x4;
    
    typedef Matrix<float, 4, 2> Flt4x2;
    typedef Matrix<float, 4, 3> Flt4x3;
    typedef Matrix<float, 4, 4> Flt4x4;
    
    typedef Matrix<double, 2, 2> Dbl2x2;
    typedef Matrix<double, 2, 3> Dbl2x3;
    typedef Matrix<double, 2, 4> Dbl2x4;
    
    typedef Matrix<double, 3, 2> Dbl3x2;
    typedef Matrix<double, 3, 3> Dbl3x3;
    typedef Matrix<double, 3, 4> Dbl3x4;
    
    typedef Matrix<double, 4, 2> Dbl4x2;
    typedef Matrix<double, 4, 3> Dbl4x3;
    typedef Matrix<double, 4, 4> Dbl4x4;
    
    typedef Matrix<Real, 2, 2> Mat2x2;
    typedef Matrix<Real, 2, 3> Mat2x3;
    typedef Matrix<Real, 2, 4> Mat2x4;
    
    typedef Matrix<Real, 3, 2> Mat3x2;
    typedef Matrix<Real, 3, 3> Mat3x3;
    typedef Matrix<Real, 3, 4> Mat3x4;
    
    typedef Matrix<Real, 4, 2> Mat4x2;
    typedef Matrix<Real, 4, 3> Mat4x3;
    typedef Matrix<Real, 4, 4> Mat4x4;
}
