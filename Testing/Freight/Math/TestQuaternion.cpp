#include <Freight/Testing.hpp>
#include <Freight/Math.hpp>
using namespace fr;

FR_TEST("Quaternion")
{
    FR_STAGE("Zero Constructor") {
        Quat a;
        FR_REQUIRE(Eql(a, {1, 0, 0, 0}));
    }

    FR_STAGE("List Constructor") {
        float l[] = {1, 2, 3, 4};
        Quat a(l);
        FR_REQUIRE(Eql(a, {1, 2, 3, 4}));
    }

    FR_STAGE("Initializer List Constructor") {
        Quat a{1, 2, 3, 4};
        FR_REQUIRE(Eql(a, {1, 2, 3, 4}));
    }

    FR_STAGE("Copy Constructor") {
        Quat a{1, 2, 3, 4};
        Quat b(a);
        FR_REQUIRE(Eql(b, {1, 2, 3, 4}));
    }

    FR_STAGE("Assignment Operator") {
        Quat a{1, 2, 3, 4};
        Quat b = a;
        FR_REQUIRE(Eql(b, {1, 2, 3, 4}));
    }

    FR_STAGE("Copy Different Type") {
        Quaternion<float> a{1, 2, 3, 4};
        Quaternion<double> b(a);
        FR_REQUIRE(Eql<double>(b, {1, 2, 3, 4}));
    }

    FR_STAGE("Multiplication Assign Operator") {
        Quat a{1, 2, 3, 4};
        Quat b{5, 6, 7, 8};
        a *= b;
        FR_REQUIRE(Eql(a, {-60, 12, 30, 24}));
    }

    FR_STAGE("Multiplication Assign Operator") {
        Quat a{0.122,0.22,0.38,0.42};
        Quat b{0.59,0.16,0.71,0.84};
        FR_REQUIRE(Eql(a * b, {-0.58582,0.17032,0.19322,0.44568}, 0.0001f));
    }
};