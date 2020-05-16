#pragma once
#include <iostream>
#include <initializer_list>
#include "Vector.hpp"
#include "../Defines.hpp"

namespace fr
{
    // M rows of vectors with depth N
    template <class T, unsigned int M, unsigned int N>
    class Matrix
    {
    public:
        
        
        inline Matrix() {}
        
        
        inline Matrix(const T(&v)[M][N]) {
            for (unsigned int i = 0; i < M; ++i) {
                mRows[i] = Vector<T, N>(v[i]);
            }
        }


        inline Matrix &operator= (const T(&v)[M][N]) {
            for (unsigned int i = 0; i < M; ++i) {
                mRows[i] = Vector<T, N>(v[i]);
            }
            return *this;
        }


        /*inline Matrix(std::initializer_list<T> list) {
            int i = 0;
            int j = 0;
            for (auto it = std::begin(list); it != std::end(list); ++it, ++j) {
                if (j >= N) {
                    j = 0;
                    ++i;
                }
                if (i >= M) break;
                mRows[i][j] = *it;
            }
        }*/


        inline Matrix(std::initializer_list<Vector<T, N>> list) {
            unsigned int i = 0;
            for (auto it = std::begin(list); it != std::end(list); ++i, ++it) {
                if (i >= M) break;
                mRows[i] = *it;
            }
        }


        inline Matrix(const Matrix &m) {
            for (unsigned int i = 0; i < M; ++i)
                mRows[i] = m.mRows[i];
        }


        inline Matrix& operator= (const Matrix &m) {
            for (unsigned int i = 0; i < M; ++i)
                mRows[i] = m.mRows[i];
            return *this;
        }
        
        
        template <class Tt, unsigned int Mm, unsigned int Nn>
        inline Matrix(const Matrix<Tt, Mm, Nn> &m) {
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
        inline Matrix &operator= (const Matrix<Tt, Mm, Nn> &m) = delete;


        ~Matrix() {}


        template <unsigned int Q>
        inline Matrix<T, M, Q> operator* (const Matrix<T, N, Q> &other) const {
            Matrix<T, M, Q> ret;
            for (unsigned int m = 0; m < M; ++m) {
                for (unsigned int q = 0; q < Q; ++q) {
                    for (unsigned int n = 0; n < N; ++n) {
                        ret[m][q] += at(m, n) * other.at(n, q);
                    }
                }
            }
            return ret;
        }


        inline Vector<T, N> operator* (const Vector<T, N> &other) const {
            Vector<T, N> ret;
            for (unsigned int m = 0; m < M; ++m) {
                for (unsigned int n = 0; n < N; ++n) {
                    ret[m] += at(m, n) * other.at(n);
                }
            }
            return ret;
        }


        inline Matrix operator* (T s) const {
            Matrix ret;
            for (unsigned int i = 0; i < M; ++i)
                ret.mRows[i] = mRows[i] * s;
            return ret;
        }


        inline Matrix operator/ (T s) const {
            Matrix ret;
            for (unsigned int i = 0; i < M; ++i)
                ret.mRows[i] = mRows[i] / s;
            return ret;
        }
        
        
        inline Matrix &operator*= (T s) {
            for (unsigned int i = 0; i < M; ++i)
                mRows[i] *= s;
            return *this;
        }


        inline Matrix &operator/= (T s) {
            for (unsigned int i = 0; i < M; ++i)
                mRows[i] /= s;
            return *this;
        }


        inline Matrix &operator+= (const Matrix &m) {
            for (unsigned int i = 0; i < M; ++i) {
                for (unsigned int j = 0; j < N; ++j) {
                    mRows[i][j] += m[i][j];
                }
            }
            return *this;
        }


        inline Matrix &operator+ (const Matrix &m) {
            Matrix ret = *this;
            ret += m;
            return m;
        }


        inline Matrix &operator-= (const Matrix &m) {
            for (unsigned int i = 0; i < M; ++i) {
                for (unsigned int j = 0; j < N; ++j) {
                    mRows[i][j] -= m[i][j];
                }
            }
            return *this;
        }


        inline Matrix &operator- (const Matrix &m) {
            Matrix ret = *this;
            ret -= m;
            return m;
        }


        inline Vector<T, N> &operator[] (unsigned int i) {
            return mRows[i];
        }


        inline const Vector<T, N> &operator[] (unsigned int i) const {
            return mRows[i];
        }


        inline T at(unsigned int i, unsigned int j) const {
            return mRows[i].at(j);
        }


        inline Matrix<T, M - 1, N - 1> minor(unsigned int i, unsigned int j) const {
            const unsigned int M2 = M - 1;
            const unsigned int N2 = N - 1;
            Matrix<T, M - 1, N - 1> ret;
            
            unsigned int ai = 0;
            unsigned int bi = 0;
            for (; ai < M; ++ai) {
                if (ai == i) continue;

                unsigned int aj = 0;
                unsigned int bj = 0;
                for (; aj < N; ++aj) {
                    if (aj == j) continue;
                    ret[bi][bj] = this->at(ai, aj);
                    ++bj;
                }
                ++bi;
            }

            return ret;
        }


        inline Matrix<T, N, M> transpose() const {
            Matrix<T, N, M> ret;
            for (unsigned int i = 0; i < M; ++i) {
                for (unsigned int j = 0; j < N; ++j) {
                    ret[j][i] = mRows[i][j];
                }
            }
            return ret;
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
    typedef Mat2x2 Mat2;
    
    typedef Matrix<Real, 3, 2> Mat3x2;
    typedef Matrix<Real, 3, 3> Mat3x3;
    typedef Matrix<Real, 3, 4> Mat3x4;
    typedef Mat3x3 Mat3;
    
    typedef Matrix<Real, 4, 2> Mat4x2;
    typedef Matrix<Real, 4, 3> Mat4x3;
    typedef Matrix<Real, 4, 4> Mat4x4;
    typedef Mat4x4 Mat4;
}
