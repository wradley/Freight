#include <Freight/Testing.hpp>
#include <Freight/Math.hpp>
using namespace fr;

FR_TEST("Matrix Zero Constructor")
{
    FR_STAGE("2x2") {
        Mat2 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0 },
            { 0, 0 }
        }));
    }

    FR_STAGE("2x3") {
        Mat2x3 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0, 0 },
            { 0, 0, 0 }
        }));
    }

    FR_STAGE("2x4") {
        Mat2x4 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }));
    }

    FR_STAGE("3x2") {
        Mat3x2 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0 },
            { 0, 0 },
            { 0, 0 }
        }));
    }

    FR_STAGE("3x3") {
        Mat3 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        }));
    }

    FR_STAGE("3x4") {
        Mat3x4 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }));
    }

    FR_STAGE("4x2") {
        Mat4x2 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0 },
            { 0, 0 },
            { 0, 0 },
            { 0, 0 }
        }));
    }

    FR_STAGE("4x3") {
        Mat4x3 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        }));
    }

    FR_STAGE("4x4") {
        Mat4 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }));
    }
};


FR_TEST("Matrix Array Constructor")
{
    FR_STAGE("2x2") {
        Real arr[2][2] = {
            { 1, 2 },
            { 3, 4 }
        };
        Mat2x2 a(arr);
        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 }
        }));
    }

    FR_STAGE("2x3") {
        Real arr[2][3] = {
            { 1, 2, 3 },
            { 4, 5, 6 }
        };
        Mat2x3 a(arr);
        FR_REQUIRE(Eql(a, {
            { 1, 2, 3 },
            { 4, 5, 6 }
        }));
    }

    FR_STAGE("2x4") {
        Real arr[2][4] = {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        };
        Mat2x4 a(arr);
        FR_REQUIRE(Eql(a, {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        }));
    }

    FR_STAGE("3x2") {
        Real arr[3][2] = {
            { 1, 2 },
            { 3, 4 },
            { 5, 6 }
        };
        Mat3x2 a(arr);
        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 },
            { 5, 6 }
        }));
    }

    FR_STAGE("3x3") {
        Real arr[3][3] = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        Mat3x3 a(arr);
        FR_REQUIRE(Eql(a, {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        }));
    }

    FR_STAGE("3x4") {
        Real arr[3][4] = {
            { 1,  2,  3,  4 },
            { 5,  6,  7,  8 },
            { 9, 10, 11, 12 }
        };
        Mat3x4 a(arr);
        FR_REQUIRE(Eql(a, {
            { 1,  2,  3,  4 },
            { 5,  6,  7,  8 },
            { 9, 10, 11, 12 }
        }));
    }

    FR_STAGE("4x2") {
        Real arr[4][2] = {
            { 1, 2 },
            { 3, 4 },
            { 5, 6 },
            { 7, 8 }
        };
        Mat4x2 a(arr);
        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 },
            { 5, 6 },
            { 7, 8 }
        }));
    }

    FR_STAGE("4x3") {
        Real arr[4][3] = {
            {  1,  2,  3 },
            {  4,  5,  6 },
            {  7,  8,  9 },
            { 10, 11, 12 },
        };
        Mat4x3 a(arr);
        FR_REQUIRE(Eql(a, {
            {  1,  2,  3 },
            {  4,  5,  6 },
            {  7,  8,  9 },
            { 10, 11, 12 },
        }));
    }

    FR_STAGE("4x4") {
        Real arr[4][4] = {
            {  1,  2,  3,  4 },
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 },
            { 13, 14, 15, 16 },
        };
        Mat4x4 a(arr);
        FR_REQUIRE(Eql(a, {
            {  1,  2,  3,  4 },
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 },
            { 13, 14, 15, 16 },
        }));
    }
};


FR_TEST("Matrix Initializer List Constructor")
{
    FR_STAGE("2x2") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };
        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 }
        }));
    }

    FR_STAGE("2x3") {
        Mat2x3 a({
            { 1, 2, 3 },
            { 4, 5, 6 }
        });
        FR_REQUIRE(Eql(a, {
            { 1, 2, 3 },
            { 4, 5, 6 }
        }));
    }

    FR_STAGE("2x4") {
        Mat2x4 a{
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        };
        FR_REQUIRE(Eql(a, {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        }));
    }

    FR_STAGE("3x2") {
        Mat3x2 a({
            { 1, 2 },
            { 3, 4 },
            { 5, 6 }
        });
        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 },
            { 5, 6 }
        }));
    }

    FR_STAGE("3x3") {
        Mat3 a{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        FR_REQUIRE(Eql(a, {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        }));
    }

    FR_STAGE("3x4") {
        Mat3x4 a({
            { 1,  2,  3,  4 },
            { 5,  6,  7,  8 },
            { 9, 10, 11, 12 }
        });
        FR_REQUIRE(Eql(a, {
            { 1,  2,  3,  4 },
            { 5,  6,  7,  8 },
            { 9, 10, 11, 12 }
        }));
    }

    FR_STAGE("4x2") {
        Mat4x2 a{
            { 1, 2 },
            { 3, 4 },
            { 5, 6 },
            { 7, 8 }
        };
        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 },
            { 5, 6 },
            { 7, 8 }
        }));
    }

    FR_STAGE("4x3") {
        Mat4x3 a({
            {  1,  2,  3 },
            {  4,  5,  6 },
            {  7,  8,  9 },
            { 10, 11, 12 },
        });
        FR_REQUIRE(Eql(a, {
            {  1,  2,  3 },
            {  4,  5,  6 },
            {  7,  8,  9 },
            { 10, 11, 12 },
        }));
    }

    FR_STAGE("4x4") {
        Mat4 a{
            {  1,  2,  3,  4 },
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 },
            { 13, 14, 15, 16 },
        };
        FR_REQUIRE(Eql(a, {
            {  1,  2,  3,  4 },
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 },
            { 13, 14, 15, 16 },
        }));
    }
};

FR_TEST("Matrix Initializer List Constructor (Differing Sizes)")
{
    FR_STAGE("2x2") {
        Mat2 a{
            { 1, 2 }
        };
        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 0, 0 }
        }));
    }

    FR_STAGE("2x3") {
        Mat2x3 a({
            { 1, 2 },
            { 4, 5 }
        });
        FR_REQUIRE(Eql(a, {
            { 1, 2, 0 },
            { 4, 5, 0 }
        }));
    }

    FR_STAGE("2x4") {
        Mat2x4 a{
            { 1, 2, 3 },
            { 5, 6, 7, 8 }
        };
        FR_REQUIRE(Eql(a, {
            { 1, 2, 3, 0 },
            { 5, 6, 7, 8 }
        }));
    }

    FR_STAGE("3x2") {
        Mat3x2 a({
            { 1 },
        });
        FR_REQUIRE(Eql(a, {
            { 1, 0 },
            { 0, 0 },
            { 0, 0 }
        }));
    }

    FR_STAGE("3x3") {
        Mat3 a{
            { 1, 2 },
            { 4, 5 },
        };
        FR_REQUIRE(Eql(a, {
            { 1, 2, 0 },
            { 4, 5, 0 },
            { 0, 0, 0 }
        }));
    }

    FR_STAGE("3x4") {
        Mat3x4 a({
            {  1,  2,  3,  4 },
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 },
            { 13, 14, 15, 16 }
        });
        FR_REQUIRE(Eql(a, {
            { 1,  2,  3,  4 },
            { 5,  6,  7,  8 },
            { 9, 10, 11, 12 }
        }));
    }

    FR_STAGE("4x2") {
        Mat4x2 a{
            { 1, 2, 1, 2 },
            { 3, 4 },
            { 5, 6 },
            { 7, 8 }
        };
        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 },
            { 5, 6 },
            { 7, 8 }
        }));
    }

    FR_STAGE("4x3") {
        Mat4x3 a({
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        });
        FR_REQUIRE(Eql(a, {
            { 1, 2, 3 },
            { 5, 6, 7 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        }));
    }

    FR_STAGE("4x4") {
        Mat4 a{
            {  1,  2,  3,  4,  5 },
            {  6,  7,  8,  9, 10 },
            { 11, 12, 13, 14, 15 },
            { 16, 17, 18, 19, 20 },
            { 21, 22, 23, 24, 25 },
        };
        FR_REQUIRE(Eql(a, {
            {  1,  2,  3,  4 },
            {  6,  7,  8,  9 },
            { 11, 12, 13, 14 },
            { 16, 17, 18, 19 },
        }));
    }
};


FR_TEST("Matrix Copy Constructor")
{
    FR_STAGE("2x2") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };
        Mat2 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("2x3") {
        Mat2x3 a{
            { 1, 2, 3 },
            { 4, 5, 6 }
        };
        Mat2x3 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("2x4") {
        Mat2x4 a{
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        };
        Mat2x4 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("3x2") {
        Mat3x2 a{
            { 1, 2 },
            { 3, 4 },
            { 5, 6 }
        };
        Mat3x2 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("3x3") {
        Mat3 a{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        Mat3 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("3x4") {
        Mat3x4 a{
            { 1,  2,  3,  4 },
            { 5,  6,  7,  8 },
            { 9, 10, 11, 12 }
        };
        Mat3x4 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("4x2") {
        Mat4x2 a{
            { 1, 2 },
            { 3, 4 },
            { 5, 6 },
            { 7, 8 }
        };
        Mat4x2 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("4x3") {
        Mat4x3 a{
            {  1,  2,  3 },
            {  4,  5,  6 },
            {  7,  8,  9 },
            { 10, 11, 12 },
        };
        Mat4x3 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("4x4") {
        Mat4 a{
            {  1,  2,  3,  4 },
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 },
            { 13, 14, 15, 16 },
        };
        Mat4 b(a);
        FR_REQUIRE(Eql(a, b));
    }
};


FR_TEST("Matrix Copy Constructor for (Differing Sizes)")
{
    FR_STAGE("Larger N") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };
        Mat2x3 b(a);
        FR_REQUIRE(Eql(b, {
            { 1, 2, 0 },
            { 3, 4, 0 }
        }));
    }

    FR_STAGE("Larger M") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };
        Mat3x2 b(a);
        FR_REQUIRE(Eql(b, {
            { 1, 2 },
            { 3, 4 },
            { 0, 0 }
        }));
    }

    FR_STAGE("Larger M & N") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };
        Mat3 b(a);
        FR_REQUIRE(Eql(b, {
            { 1, 2, 0 },
            { 3, 4, 0 },
            { 0, 0, 0 },
        }));
    }

    FR_STAGE("Smaller N") {
        Mat3 a{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        Mat3x2 b(a);
        FR_REQUIRE(Eql(b, {
            { 1, 2 },
            { 4, 5 },
            { 7, 8 }
        }));
    }

    FR_STAGE("Smaller M") {
        Mat3 a{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        Mat2x3 b(a);
        FR_REQUIRE(Eql(b, {
            { 1, 2, 3 },
            { 4, 5, 6 }
        }));
    }

    FR_STAGE("Smaller M & N") {
        Mat3 a{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        Mat2 b(a);
        FR_REQUIRE(Eql(b, {
            { 1, 2 },
            { 4, 5 }
        }));
    }

    FR_STAGE("Two to Four") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };
        Mat4 b(a);
        FR_REQUIRE(Eql(b, {
            { 1, 2, 0, 0 },
            { 3, 4, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }));
    }

    FR_STAGE("Four to Two") {
        Mat4 a{
            {  1,  2,  3,  4 },
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 },
            { 13, 14, 15, 16 }
        };
        Mat2 b(a);
        FR_REQUIRE(Eql(b, {
            { 1, 2 },
            { 5, 6 }
        }));
    }
};


FR_TEST("Assign Operator")
{
    FR_STAGE("2x2") {
        Mat2 a{
            { 1, 2 },
            { 3, 4 }
        };
        Mat2 b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("2x3") {
        Mat2x3 a{
            { 1, 2, 3 },
            { 4, 5, 6 }
        };
        Mat2x3 b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("2x4") {
        Mat2x4 a{
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 }
        };
        Mat2x4 b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("3x2") {
        Mat3x2 a{
            { 1, 2 },
            { 3, 4 },
            { 5, 6 }
        };
        Mat3x2 b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("3x3") {
        Mat3 a{
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        Mat3 b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("3x4") {
        Mat3x4 a{
            { 1,  2,  3,  4 },
            { 5,  6,  7,  8 },
            { 9, 10, 11, 12 }
        };
        Mat3x4 b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("4x2") {
        Mat4x2 a{
            { 1, 2 },
            { 3, 4 },
            { 5, 6 },
            { 7, 8 }
        };
        Mat4x2 b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("4x3") {
        Mat4x3 a{
            {  1,  2,  3 },
            {  4,  5,  6 },
            {  7,  8,  9 },
            { 10, 11, 12 },
        };
        Mat4x3 b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("4x4") {
        Mat4 a{
            {  1,  2,  3,  4 },
            {  5,  6,  7,  8 },
            {  9, 10, 11, 12 },
            { 13, 14, 15, 16 },
        };
        Mat4 b = a;
        FR_REQUIRE(Eql(a, b));
    }
};