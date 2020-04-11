#include <Freight/Testing.hpp>
#include "../../Source/Freight/Math/Vector.hpp"

FR_TEST("Vector 2")
{
    FR_STAGE("Zero Constructor") {
        fr::Vec2 a;
        FR_REQUIRE(a[0] == 0.0f && a[1] == 0.0f);
    }
    
    FR_STAGE("Copy Constructor") {
        fr::Vec2 a({1, 2});
        fr::Vec2 b(a);
        FR_REQUIRE(b[0] == 1.0f && b[1] == 2.0f);
    }

    FR_STAGE("Assign Operator") {
        fr::Vec2 a({1, 2});
        fr::Vec2 b;
        b = a;
        FR_REQUIRE(b[0] == 1.0f && b[1] == 2.0f);
    }

    FR_STAGE("Copy Constructor Vec3") {
        fr::Vec3 a({1, 2, 3});
        fr::Vec2 b(a);
        FR_REQUIRE(b[0] == 1.0f && b[1] == 2.0f);
    }

    FR_STAGE("Copy Constructor Vec4") {
        fr::Vec4 a({1, 2, 3, 4});
        fr::Vec2 b(a);
        FR_REQUIRE(b[0] == 1.0f && b[1] == 2.0f);
    }

    FR_STAGE("List Constructor") {
        float a[] = {1,2};
        fr::Vec2 b(a);
        FR_REQUIRE(b[0] == 1.0f && b[1] == 2.0f);
    }

    FR_STAGE("Initializer List Constructor") {
        fr::Vec2 a({1, 2});
        FR_REQUIRE(a[0] == 1.0f && a[1] == 2.0f);
    }

    FR_STAGE("Smaller Initializer List Constructor") {
        fr::Vec2 a({1});
        FR_REQUIRE(a[0] == 1.0f && a[1] == 0.0f);
    }

    FR_STAGE("Larger Initializer List Constructor") {
        fr::Vec2 a({1, 2, 3});
        FR_REQUIRE(a[0] == 1.0f && a[1] == 2.0f);
    }

    FR_STAGE("Assign List Operator") {
        float a[] = {1, 2};
        fr::Vec2 b;
        b = a;
        FR_REQUIRE(b[0] == 1.0f && b[1] == 2.0f);
    }

    FR_STAGE("Plus Operator") {
        fr::Vec2 a({1,2});
        fr::Vec2 b({3,4});
        fr::Vec2 c(a + b);
        FR_REQUIRE(c[0] == 4.0f && c[1] == 6.0f);
    };

    FR_STAGE("Minus Operator") {
        fr::Vec2 a({1,2});
        fr::Vec2 b({3,5});
        fr::Vec2 c(a + b);
        FR_REQUIRE(c[0] == -2.0f && c[1] == -3.0f);
    };

    FR_STAGE("Multiplication Operator") {
        fr::Vec2 a({1,2});
        float b = 3;
        fr::Vec2 c = a * b;
        FR_REQUIRE(c[0] == 2.0f && c[1] == 6.0f);
    };

    FR_STAGE("Division Operator") {
        fr::Vec2 a({3,6});
        float b = 3;
        fr::Vec2 c = a / b;
        FR_REQUIRE(c[0] == 1.0f && c[1] == 2.0f);
    };

    FR_STAGE("Plus Assign Operator") {
        fr::Vec2 a({1,2});
        fr::Vec2 b({3,4});
        b += a;
        FR_REQUIRE(b[0] == 4.0f && b[1] == 6.0f);
    };

    FR_STAGE("Minus Assign Operator") {
        fr::Vec2 a({1,2});
        fr::Vec2 b({3,5});
        b -= a;
        FR_REQUIRE(b[0] == -2.0f && b[1] == -3.0f);
    };

    FR_STAGE("Times Assign Operator") {
        float a(2);
        fr::Vec2 b({1,2});
        b *= a;
        FR_REQUIRE(b[0] == 2.0f && b[1] == 4.0f);
    };

    FR_STAGE("Divide Assign Operator") {
        float a(2);
        fr::Vec2 b({1,2});
        b /= a;
        FR_REQUIRE(b[0] == 0.5f && b[1] == 1.0f);
    };

    FR_STAGE("Equal Operator") {
        fr::Vec2 a({1,2});
        fr::Vec2 b({1,2});
        FR_REQUIRE(a == b);
    };

    FR_STAGE("Not Equal Operator") {
        fr::Vec2 a({2,2});
        fr::Vec2 b({1,2});
        FR_REQUIRE(a != b);
    };

    FR_STAGE("Length") {
        fr::Vec2 a({2,2});
        FR_REQUIRE(a.getLength() == 2.8284271247f);
    };

    FR_STAGE("Normalized") {
        fr::Vec2 a({1,1});
        auto b = a.getNormalized();
        FR_REQUIRE(b[0] == 0.7071067812f && b[1] == 0.7071067812f);
    };

    FR_STAGE("Normalize") {
        fr::Vec2 a({1,1});
        a.normalize();
        FR_REQUIRE(a[0] == 0.7071067812f && a[1] == 0.7071067812f);
    };

    FR_STAGE("Dot 0 Degrees") {
        fr::Vec2 a({1,0});
        fr::Vec2 b({1,0});
        auto d = a.dot(b);
        FR_REQUIRE(a.dot(b) == 1.0f);
    };

    FR_STAGE("Dot 45 Degrees") {
        fr::Vec2 a({1,0});
        fr::Vec2 b({1,1});
        auto d = a.dot(b);
        FR_REQUIRE(a.dot(b) == 1.0f);
    };

    FR_STAGE("Dot 90 Degrees") {
        fr::Vec2 a({1,0});
        fr::Vec2 b({0,1});
        auto d = a.dot(b);
        FR_REQUIRE(a.dot(b) == 0.0f);
    };

    FR_STAGE("Dot 135 Degrees") {
        fr::Vec2 a({1,0});
        fr::Vec2 b({1,1});
        auto d = a.dot(b);
        FR_REQUIRE(a.dot(b) == 1.0f);
    };

    FR_STAGE("Dot 180 Degrees") {
        fr::Vec2 a({1,0});
        fr::Vec2 b({-1,0});
        auto d = a.dot(b);
        FR_REQUIRE(a.dot(b) == 1.0f);
    };
};