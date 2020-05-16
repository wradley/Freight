#include <Freight/Testing.hpp>
#include <Freight/Math.hpp>
using namespace fr;

FR_TEST("Matrix Transpose")
{
    FR_STAGE("Mat2") {
        Mat2 m{
            { 1, 2 },
            { 3, 4 }
        };

        FR_REQUIRE(Eql(Transpose(m), {
            { 1, 3 },
            { 2, 4 }
        }));
    }

    FR_STAGE("Mat2x3") {
        Mat2x3 m{
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        FR_REQUIRE(Eql(Transpose(m), {
            { 1, 4 },
            { 2, 5 },
            { 3, 6 }
        }));
    }

    FR_STAGE("Mat2x4") {
        Mat2x4 m{
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        };

        FR_REQUIRE(Eql(Transpose(m), {
            { 1, 5 },
            { 2, 6 },
            { 3, 7 },
            { 4, 8 }
        }));
    }

    FR_STAGE("Mat3x2") {
        Mat3x2 m{
            { 1, 2 },
            { 3, 4 },
            { 5, 6 }
        };

        FR_REQUIRE(Eql(Transpose(m), {
            { 1, 3, 5 },
            { 2, 4, 6 }
        }));
    }

    FR_STAGE("Mat3") {
        Mat3 m{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        FR_REQUIRE(Eql(Transpose(m), {
            { 1, 4, 7 },
            { 2, 5, 8 },
            { 3, 6, 9 }
        }));
    }

    FR_STAGE("Mat3x4") {
        Mat3x4 m{
            { 1,  2,  3,  4 },
            { 5,  6,  7,  8 },
            { 9, 10, 11, 12 }
        };

        FR_REQUIRE(Eql(Transpose(m), {
            { 1, 5,  9 },
            { 2, 6, 10 },
            { 3, 7, 11 },
            { 4, 8, 12 }
        }));
    }

    FR_STAGE("Mat4x2") {
        Mat4x2 m{
            { 1, 2 },
            { 3, 4 },
            { 5, 6 },
            { 7, 8 }
        };

        FR_REQUIRE(Eql(Transpose(m), {
            { 1, 3, 5, 7 },
            { 2, 4, 6, 8 }
        }));
    }

    FR_STAGE("Mat4x3") {
        Mat4x3 m{
            {  1,  2,  3 },
            {  4,  5,  6 },
            {  7,  8,  9 },
            { 10, 11, 12 }
        };

        FR_REQUIRE(Eql(Transpose(m), {
            { 1, 4, 7, 10 },
            { 2, 5, 8, 11 },
            { 3, 6, 9, 12 },
        }));
    }

    FR_STAGE("Mat4") {
        Mat4 m{
            {  1,  2,  3,  4 },
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 },
            { 13, 14, 15, 16 }
        };

        FR_REQUIRE(Eql(Transpose(m), {
            { 1, 5,  9, 13 },
            { 2, 6, 10, 14 },
            { 3, 7, 11, 15 },
            { 4, 8, 12, 16 },
        }));
    }
};