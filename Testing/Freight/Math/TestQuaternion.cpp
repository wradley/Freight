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

    FR_STAGE("Smaller Initializer List Constructor") {
        Quat a{1, 2, 3};
        FR_REQUIRE(Eql(a, {1, 2, 3, 0}));
    }

    FR_STAGE("Larger Initializer List Constructor") {
        Quat a{1, 2, 3, 4, 5};
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

    FR_STAGE("Multiplication") {
        Quat a{0.122,0.22,0.38,0.42};
        Quat b{0.59,0.16,0.71,0.84};
        FR_REQUIRE(Eql(a * b, {-0.58582,0.17032,0.19322,0.44568}, 0.0001f));
    }

    FR_STAGE("Rotating Point by Unit Quaternion 1") {
        Quat r = AxisAngleToQuat({1, 0, 0}, ToRad(90));
        Vec3 pt{0, 0, 1};
        FR_REQUIRE(Eql(Normal(r * pt), {0, -1, 0}));
    }

    FR_STAGE("Rotating Point by Unit Quaternion 2") {
        Quat r = AxisAngleToQuat(Normal(Vec3{1, 7, 3.1}), ToRad(39.1));
        Vec3 pt = Normal(Vec3{8, 5, 1});
        FR_REQUIRE(Eql(Normal(r * pt), {0.59949f, 0.74174f, -0.30074f}, 0.0001f));
    }

    FR_STAGE("+ Vector3") {
        unsigned int iterations = 1000;
        Vec3 axis = Normal(Vec3{1,2,3});
        Real deg = 360;

        Quat orientation{1, 0, 0, 0};
        Vec3 r1 = Normal(Vec3{1, 0, 0}) * ToRad(0.09);
        Vec3 rotation = Normal(axis) * ToRad(deg / (Real) iterations);

        for (unsigned int i = 0; i < iterations; ++i) {
            orientation += rotation;
            orientation.normalize();
        }

        auto pt = orientation * Vec3{0, 1, 0};

        FR_REQUIRE(Eql(pt, {0, 1, 0}, 0.0001f));
    }

    FR_STAGE("+= Vector3") {
        unsigned int iterations = 1000;
        Vec3 axis = Normal(Vec3{2.01,2,3});
        Vec3 initPt{0, 1, 0};
        Real deg = 88;

        Quat orientation{1, 0, 0, 0};
        Vec3 r1 = Normal(Vec3{1, 0, 0}) * ToRad(0.09);
        Vec3 rotation = Normal(axis) * ToRad(deg / (Real)iterations);

        for (unsigned int i = 0; i < iterations; ++i) {
            orientation = orientation + rotation;
            orientation.normalize();
        }

        auto pt = orientation * initPt;

        FR_REQUIRE(Eql(pt, AxisAngleToQuat(axis, ToRad(deg)) * initPt, 0.0001f));
    }

    FR_STAGE("Length") {
        Quat a{1, 2, 3, 4};
        FR_REQUIRE(Eql(a.getLength(), 5.477226f, 0.00001f));
    }

    FR_STAGE("Normalize") {
        Quat a{1, 2, 3, 4};
        FR_REQUIRE(Eql(a.getNormalized(), {0.18257f, 0.36514f, 0.54772f, 0.73029f}, 0.0001f));
    }

    FR_STAGE("Normalize Self") {
        Quat a{1, 2, 3, 4};
        FR_REQUIRE(Eql(a.normalize(), {0.18257f, 0.36514f, 0.54772f, 0.73029f}, 0.0001f));
    }

    FR_STAGE("[] operator") {
        Quat a{1, 2, 3, 4};
        FR_REQUIRE(Eql(a[0], 1) && Eql(a[1], 2) && Eql(a[2], 3) && Eql(a[3], 4));
    }

    FR_STAGE("const [] operator") {
        const Quat a{1, 2, 3, 4};
        FR_REQUIRE(Eql(a[0], 1) && Eql(a[1], 2) && Eql(a[2], 3) && Eql(a[3], 4));
    }
};