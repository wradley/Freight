#include <Freight/Testing.hpp>
#include <Freight/Math.hpp>
using namespace fr;

FR_TEST("Matrix 2x2")
{
    FR_STAGE("Zero Constructor") {
        Mat2 a;
        FR_REQUIRE(Eql(a, {
            { 0, 0 },
            { 0, 0 }
        }));
    }

    FR_STAGE("Array Constructor") {
        Real arr[2][2] = {
            { 1, 2 },
            { 3, 4 }
        };

        Mat2 a(arr);

        FR_REQUIRE(Eql(a, {
            { 1, 2 },
            { 3, 4 }
        }));
    }
};