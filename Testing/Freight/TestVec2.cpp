#include <Freight/Testing.hpp>
#include "../../Source/Freight/Math/Vector.hpp"
#include "../../Source/Freight/Math/Conversion.hpp"
#include <Freight.hpp>
using namespace fr;

FR_TEST("Vector 2")
{
    FR_STAGE("Zero Constructor") {
        Vec2 a;
        FR_REQUIRE(Eql(a[0], 0.0f) && Eql(a[1], 0.0f));
    }
    
    FR_STAGE("Copy Constructor") {
        Vec2 a({1, 2});
        Vec2 b(a);
        FR_REQUIRE(Eql(b[0], 1.0f) && Eql(b[1], 2.0f));
    }

    FR_STAGE("Assign Operator") {
        Vec2 a({1, 2});
        Vec2 b;
        b = a;
        FR_REQUIRE(Eql(b[0], 1.0f) && Eql(b[1], 2.0f));
    }

    FR_STAGE("Copy Constructor Vec3") {
        Vec3 a({1, 2, 3});
        Vec2 b(a);
        FR_REQUIRE(Eql(b[0], 1.0f) && Eql(b[1], 2.0f));
    }

    FR_STAGE("Copy Constructor Vec4") {
        Vec4 a({1, 2, 3, 4});
        Vec2 b(a);
        FR_REQUIRE(Eql(b[0], 1.0f) && Eql(b[1], 2.0f));
    }

    FR_STAGE("List Constructor") {
        float a[] = {1, 2};
        Vec2 b(a);
        FR_REQUIRE(Eql(b[0], 1.0f) && Eql(b[1], 2.0f));
    }

    FR_STAGE("Initializer List Constructor") {
        Vec2 a{1, 2};
        FR_REQUIRE(Eql(a[0], 1.0f) && Eql(a[1], 2.0f));
    }

    FR_STAGE("Small Initializer List Constructor") {
        Vec2 a{1};
        FR_REQUIRE(Eql(a[0], 1.0f) && Eql(a[1], 0.0f));
    }

    FR_STAGE("Large Initializer List Constructor") {
        Vec2 a{1, 2, 3};
        FR_REQUIRE(Eql(a[0], 1.0f) && Eql(a[1], 2.0f));
    }


    FR_STAGE("Assign List Operator") {
        float a[] = {1, 2};
        Vec2 b;
        b = a;
        FR_REQUIRE(Eql(b[0], 1.0f) && Eql(b[1], 2.0f));
    }

    FR_STAGE("Plus Operator") {
        Vec2 a({1,2});
        Vec2 b({3,4});
        Vec2 c(a + b);
        FR_REQUIRE(Eql(c[0], 4.0f) && Eql(c[1], 6.0f));
    };

    FR_STAGE("Minus Operator") {
        Vec2 a({1,2});
        Vec2 b({3,5});
        Vec2 c(a - b);
        FR_REQUIRE(Eql(c[0], -2.0f) && Eql(c[1], -3.0f));
    };

    FR_STAGE("Multiplication Operator") {
        Vec2 a({1,2});
        float b = 3;
        Vec2 c = a * b;
        FR_REQUIRE(Eql(c[0], 3.0f) && Eql(c[1], 6.0f));
    };

    FR_STAGE("Division Operator") {
        Vec2 a({3,6});
        float b = 3;
        Vec2 c = a / b;
        FR_REQUIRE(Eql(c[0], 1.0f) && Eql(c[1], 2.0f));
    };

    FR_STAGE("Plus Assign Operator") {
        Vec2 a({1,2});
        Vec2 b({3,4});
        b += a;
        FR_REQUIRE(Eql(b[0], 4.0f) && Eql(b[1], 6.0f));
    };

    FR_STAGE("Minus Assign Operator") {
        Vec2 a({1,2});
        Vec2 b({3,5});
        a -= b;
        FR_REQUIRE(Eql(a[0], -2.0f) && Eql(a[1], -3.0f));
    };

    FR_STAGE("Times Assign Operator") {
        float a(2);
        Vec2 b({1,2});
        b *= a;
        FR_REQUIRE(Eql(b[0], 2.0f) && Eql(b[1], 4.0f));
    };

    FR_STAGE("Divide Assign Operator") {
        float a(2);
        Vec2 b({1,2});
        b /= a;
        FR_REQUIRE(Eql(b[0], 0.5f) && Eql(b[1], 1.0f));
    };

    // FR_STAGE("Equal Operator") {
    //     Vec2 a({1,2});
    //     Vec2 b({1,2});
    //     FR_REQUIRE(a == b); remove?
    // };

    // FR_STAGE("Not Equal Operator") {
    //     Vec2 a({2,2});
    //     Vec2 b({1,2});
    //     FR_REQUIRE(a != b);
    // };

    FR_STAGE("Length") {
        fr::Vec2 a({2,2});
        FR_REQUIRE(Eql(a.getLength(), 2.828f, 0.001f));
    };

    FR_STAGE("Normalized") {
        Vec2 a({1,1});
        auto b = a.getNormalized();
        FR_REQUIRE(Eql(b[0], 0.7071f, 0.0001f) && Eql(b[1], 0.7071f, 0.0001f));
    };

    FR_STAGE("Normalize") {
        Vec2 a({1,1});
        a.normalize();
        FR_REQUIRE(Eql(a[0], 0.7071f, 0.0001f) && Eql(a[1], 0.7071f, 0.0001f));
    };

    FR_STAGE("Dot 0 Degrees") {
        Vec2 a = Normal(Vec2{1,1});
        Vec2 b = Normal(Vec2{1,1});
        FR_REQUIRE(Eql(a.dot(b), 1.0f));
    };

    FR_STAGE("Dot 45 Degrees") {
        Mat2 R = Rotate2D(ToRad(22.5));
        Vec2 a = R * Normal(Vec2{0,1});
        Vec2 b = R * Normal(Vec2{1,1});
        FR_REQUIRE(Eql(a.dot(b), 0.7071f, 0.0001f));
    };

    FR_STAGE("Dot 90 Degrees") {
        Mat2 R = Rotate2D(ToRad(45));
        fr::Vec2 a = R * Normal(Vec2{0,1});
        fr::Vec2 b = R * Normal(Vec2{1,0});
        FR_REQUIRE(Eql(a.dot(b), 0.0f, 0.0001f));
    };

    FR_STAGE("Dot 135 Degrees") {
        fr::Vec2 a = Normal(Vec2{1,0});
        fr::Vec2 b = Normal(Vec2{-1,1});
        FR_REQUIRE(Eql(a.dot(b), -0.7071f, 0.0001f));
    };

    FR_STAGE("Dot 180 Degrees") {
        Mat2 R = Rotate2D(ToRad(45));
        fr::Vec2 a = R * Normal(Vec2{1,0});
        fr::Vec2 b = R * Normal(Vec2{-1,0});
        FR_REQUIRE(Eql(a.dot(b), -1.0f, 0.0001f));
    };
};