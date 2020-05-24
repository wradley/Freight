#include <Freight/Testing.hpp>
#include <Freight/Math.hpp>
using namespace fr;

FR_TEST("Vector 3")
{
    FR_STAGE("Zero Constructor") {
        Vec3 a;
        FR_REQUIRE(Eql(a, {0, 0, 0}));
    }
    
    FR_STAGE("Copy Constructor") {
        Vec3 a({1, 2, 3});
        Vec3 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("Assign Operator") {
        Vec3 a{1, 2, 3};
        Vec3 b;
        b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("Copy Constructor Vec2") {
        Vec2 a({1, 2});
        Vec3 b(a);
        FR_REQUIRE(Eql(b, {1, 2, 0}));
    }

    FR_STAGE("Copy Constructor Vec4") {
        Vec4 a({1, 2, 3, 4});
        Vec3 b(a);
        FR_REQUIRE(Eql(b, {1, 2, 3}));
    }

    FR_STAGE("List Constructor") {
        float a[] = {1, 2, 3};
        Vec3 b(a);
        FR_REQUIRE(Eql(b, {1, 2, 3}));
    }

    FR_STAGE("Initializer List Constructor") {
        Vec3 a{1, 2, 3};
        FR_REQUIRE(Eql(a[0], 1) && Eql(a[1], 2) && Eql(a[2], 3));
    }

    FR_STAGE("Small Initializer List Constructor") {
        Vec3 a{1, 2};
        FR_REQUIRE(Eql(a, {1, 2, 0}));
    }

    FR_STAGE("Large Initializer List Constructor") {
        Vec3 a{1, 2, 3, 4};
        FR_REQUIRE(Eql(a, {1, 2, 3}));
    }

    FR_STAGE("Assign List Operator") {
        float a[] = {1, 2, 3};
        Vec3 b;
        b = a;
        FR_REQUIRE(Eql(b, {1, 2, 3}));
    }

    FR_STAGE("Plus Operator") {
        Vec3 a{1, 2, 3};
        Vec3 b{4, 5, 6};
        auto c = a + b;
        FR_REQUIRE(Eql(c, {5, 7, 9}));
    };

    FR_STAGE("Minus Operator") {
        Vec3 a{1, 2, 3};
        Vec3 b{4, 5, 6};
        auto c = a - b;
        FR_REQUIRE(Eql(c, {-3, -3, -3}));
    };

    FR_STAGE("Multiplication Operator") {
        Vec3 a{1, 2, 3};
        auto b = a * 3;
        FR_REQUIRE(Eql(b, {3, 6, 9}));
    };

    FR_STAGE("Division Operator") {
        Vec3 a{1, 2, 3};
        auto b = a / 3;
        FR_REQUIRE(Eql(b, {0.33333f, 0.66666f, 0.99999f}, 0.0001f));
    };

    FR_STAGE("Plus Assign Operator") {
        Vec3 a{1, 2, 3};
        Vec3 b{4, 5, 6};
        b += a;
        FR_REQUIRE(Eql(b, {5, 7, 9}));
    };

    FR_STAGE("Minus Assign Operator") {
        Vec3 a{1, 2, 3};
        Vec3 b{4, 5, 6};
        b -= a;
        FR_REQUIRE(Eql(b, {3, 3, 3}));
    };

    FR_STAGE("Times Assign Operator") {
        Vec3 a{1, 2, 3};
        a *= 3;
        FR_REQUIRE(Eql(a, {3, 6, 9}));
    };

    FR_STAGE("Divide Assign Operator") {
        Vec3 a{1, 2, 3};
        a /= 3;
        FR_REQUIRE(Eql(a, {0.33333f, 0.66666f, 0.99999f}, 0.0001f));
    };

    FR_STAGE("Length") {
        fr::Vec3 a{2, 2, 2};
        FR_REQUIRE(Eql(a.getLength(), 3.46410f, 0.0001f));
    };

    FR_STAGE("Normalized") {
        Vec3 a{1, 1, 1};
        auto b = a.getNormalized();
        FR_REQUIRE(Eql(b, {0.57735f, 0.57735f, 0.57735f}, 0.0001f));
    };

    FR_STAGE("Normalize") {
        Vec3 a{1, 1, 1};
        a.normalize();
        FR_REQUIRE(Eql(a, {0.57735f, 0.57735f, 0.57735f}, 0.0001f));
    };

    FR_STAGE("Dot Zero") {
        Vec3 a;
        Vec3 b;
        FR_REQUIRE(Eql(a.dot(b), 0));
    };

    FR_STAGE("Dot Non-Zero") {
        Vec3 a{1, 2, 3};
        Vec3 b{4, 5, 6};
        FR_REQUIRE(Eql(a.dot(b), 32));
    };
};