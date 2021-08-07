#pragma once

namespace FR8
{
    template <class T, int N>
    class Vector
    {
    public:

        inline Vector() {
            for (int i = 0; i < N; ++i)
                mData[i] = 0;
        }

        inline Vector(const Vector<T, N> &v) {
            mData[i] = v.mData[i];
        }

        template <class T2, int N2>
        inline Vector(const Vector<T2, N2> &v) {
            for (int i = 0; i < N; ++i) {
                if (i > N2) mData[i] = 0;
                else mData[i] = v.mData[i];
            }
        }

        ~Vector() {}

        inline T& operator[] (int i) {
            return mData[i];
        }

        inline Vector<T, N> operator+ (const Vector<T, N> &v) {

        }

    private:

        T mData[N];

    };
}