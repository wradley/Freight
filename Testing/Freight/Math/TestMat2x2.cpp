#include <Freight/Testing.hpp>
#include <Freight/Math.hpp>
using namespace fr;

FR_TEST("Matrix 2x2")
{


    FR_STAGE("Matrix Multiplication 1") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        Mat2 b{
            { 5, 6 },
            { 7, 8 }
        };

        FR_REQUIRE(Eql(a * b, {
            { 19, 22 },
            { 43, 50 }
        }));
    }

    FR_STAGE("Matrix Multiplication 2") {
        Mat2 a{
            { 1.1, 2.2 },
            { 3.3, 4.4 }
        };

        Mat2x3 b{
            { 5, 6, 7  },
            { 8, 9, 10 }
        };

        FR_REQUIRE(Eql(a * b, {
            { 23.1, 26.4, 29.7 },
            { 51.7, 59.4, 67.1 }
        }, 0.00001f));
    }

    FR_STAGE("Matrix Multiplication 3") {
        Mat2 a{
            { 1.1, 2.2 },
            { 3.3, 4.4 }
        };

        Matrix<Real, 2, 1> b{
            { 5 },
            { 6 }
        };

        FR_REQUIRE(Eql(a * b, {
            { 18.7 },
            { 42.9 }
        }, 0.00001f));
    }

    FR_STAGE("Vector Multiplication") {
        Mat2 a{
            { 1.1, 2.2 },
            { 3.3, 4.4 }
        };

        Vec2 b{ 5, 6 };

        FR_REQUIRE(Eql(a * b, {
            { 18.7 },
            { 42.9 }
        }, 0.00001f));
    }

    FR_STAGE("Scalar Multiplication") {
        Mat2 a{
            { 1.1f, 2.2f },
            { 3.3f, 4.1f }
        };

        FR_REQUIRE(Eql(a * 41.01f, {
            {  45.111f,  90.222f },
            { 135.333f, 168.141f }
        }, 0.0001f));
    }

    FR_STAGE("Scalar Division") {
        Mat2 a{
            { 1.4, 2.9 },
            { 3.7, 4.1 }
        };

        FR_REQUIRE(Eql(a/ 41.01f, {
            { 0.034138f,0.070714f },
            { 0.090221f,0.099975f }
        }, 0.00001f));
    }

    FR_STAGE("Scalar Multiplication Assignment") {
        Mat2 a{
            { 1.1f, 2.2f },
            { 3.3f, 4.1f }
        };

        a *= 41.01f;

        FR_REQUIRE(Eql(a, {
            {  45.111f,  90.222f },
            { 135.333f, 168.141f }
        }, 0.0001f));
    }

    FR_STAGE("Scalar Division Assignment") {
        Mat2 a{
            { 1.4, 2.9 },
            { 3.7, 4.1 }
        };

        FR_REQUIRE(Eql(a / 41.01f, {
            { 0.034138f,0.070714f },
            { 0.090221f,0.099975f }
        }, 0.00001f));
    }

    FR_STAGE("[] operator") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        FR_REQUIRE(
            Eql(a[0][0], 1) &&
            Eql(a[0][1], 2) &&
            Eql(a[1][0], 3) &&
            Eql(a[1][1], 4)
        );
    }

    FR_STAGE("const [] operator") {
        const Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        FR_REQUIRE(
            Eql(a[0][0], 1) &&
            Eql(a[0][1], 2) &&
            Eql(a[1][0], 3) &&
            Eql(a[1][1], 4)
        );
    }

    FR_STAGE("Minor 1") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        FR_REQUIRE(Eql(a.minor(1, 1), {{1}}));
    }

    FR_STAGE("Minor 2") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        FR_REQUIRE(Eql(a.minor(1, 0), {{2}}));
    }

    FR_STAGE("Minor 3") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        FR_REQUIRE(Eql(a.minor(0, 1), {{3}}));
    }

    FR_STAGE("Minor 4") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        FR_REQUIRE(Eql(a.minor(0, 0), {{4}}));
    }
};