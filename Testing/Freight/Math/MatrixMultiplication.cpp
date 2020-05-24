#include <Freight/Testing.hpp>
#include <Freight/Math.hpp>
using namespace fr;

FR_TEST("Mat2 Matrix Multiplication")
{
    FR_STAGE("Mat2") {
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

    FR_STAGE("Mat2x3") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        Mat2x3 b{
            {  5,  6,  7 },
            {  8,  9, 10 }
        };

        FR_REQUIRE(Eql(a * b, {
            { 21, 24, 27 },
            { 47, 54, 61 }
        }));
    }

    FR_STAGE("Mat2x4") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };

        Mat2x3 b{
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 }
        };

        FR_REQUIRE(Eql(a * b, {
            { 23, 26, 29, 32 },
            { 51, 58, 65, 72 }
        }));
    }
};


FR_TEST("Mat2x3 Matrix Multiplication")
{
    FR_STAGE("Mat3x2") {
        Mat2x3 a{
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        Mat3x2 b{
            {  7,  8 },
            {  9, 10 },
            { 11, 12 }
        };

        FR_REQUIRE(Eql(a * b, {
            {  58,  64 },
            { 139, 154 }
        }));
    }

    FR_STAGE("Mat3") {
        Mat2x3 a{
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        Mat3 b{
            {   7,  8,  9 },
            {  10, 11, 12 },
            {  13, 14, 15 }
        };

        FR_REQUIRE(Eql(a * b, {
            {  66,  72,  78 },
            { 156, 171, 186 }
        }));
    }

    FR_STAGE("Mat3x4") {
        Mat2x3 a{
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        Mat3x4 b{
            {  7,  8,  9, 10 },
            { 11, 12, 13, 14 },
            { 15, 16, 17, 18 }
        };

        FR_REQUIRE(Eql(a * b, {
            {  74,  80,  86,  92 },
            { 173, 188, 203, 218 }
        }));
    }
};


FR_TEST("Mat2x4 Matrix Multiplication")
{
    FR_STAGE("Mat4x2") {
        Mat2x4 a{
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        };

        Mat4x2 b{
            {  9, 10 },
            { 11, 12 },
            { 13, 14 },
            { 15, 16 }
        };

        FR_REQUIRE(Eql(a * b, {
            { 130, 140 },
            { 322, 348 }
        }));
    }

    FR_STAGE("Mat4x3") {
        Mat2x4 a{
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        };

        Mat4x3 b{
            {   7,  8,  9 },
            {  10, 11, 12 },
            {  13, 14, 15 }
        };

        FR_REQUIRE(Eql(a * b, {
            {  66,  72,  78 },
            { 156, 171, 186 }
        }));
    }

    FR_STAGE("Mat4x4") {
        Mat2x4 a{
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        };

        Mat4x4 b{
            {  7,  8,  9, 10 },
            { 11, 12, 13, 14 },
            { 15, 16, 17, 18 }
        };

        FR_REQUIRE(Eql(a * b, {
            {  74,  80,  86,  92 },
            { 173, 188, 203, 218 }
        }));
    }
};