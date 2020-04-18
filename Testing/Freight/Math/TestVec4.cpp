#include <Freight/Testing.hpp>
#include <Freight/Math.hpp>
using namespace fr;

FR_TEST("Vector 4")
{
    FR_STAGE("Zero Constructor") {
        Vec4 a;
        FR_REQUIRE(Eql(a, {0, 0, 0, 0}));
    }
    
    FR_STAGE("Copy Constructor") {
        Vec4 a({1, 2, 3});
        Vec4 b(a);
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("Assign Operator") {
        Vec4 a{1, 2, 3};
        Vec4 b;
        b = a;
        FR_REQUIRE(Eql(a, b));
    }

    FR_STAGE("Copy Constructor Vec2") {
        Vec2 a({1, 2});
        Vec4 b(a);
        FR_REQUIRE(Eql(b, {1, 2, 0, 0}));
    }

    FR_STAGE("Copy Constructor Vec3") {
        Vec3 a{1, 2, 3};
        Vec4 b(a);
        FR_REQUIRE(Eql(b, {1, 2, 3, 0}));
    }

    FR_STAGE("List Constructor") {
        float a[] = {1, 2, 3, 4};
        Vec4 b(a);
        FR_REQUIRE(Eql(b, {1, 2, 3, 4}));
    }

    FR_STAGE("Initializer List Constructor") {
        Vec4 a{1, 2, 3, 4};
        FR_REQUIRE(Eql(a[0], 1) && Eql(a[1], 2) && Eql(a[2], 3) && Eql(a[3], 4));
    }

    FR_STAGE("Small Initializer List Constructor") {
        Vec4 a{1, 2};
        FR_REQUIRE(Eql(a, {1, 2, 0, 0}));
    }

    FR_STAGE("Large Initializer List Constructor") {
        Vec4 a{1, 2, 3, 4, 5};
        FR_REQUIRE(Eql(a, {1, 2, 3, 4}));
    }

    FR_STAGE("Assign List Operator") {
        float a[] = {1, 2, 3, 4};
        Vec4 b;
        b = a;
        FR_REQUIRE(Eql(b, {1, 2, 3, 4}));
    }

    FR_STAGE("Plus Operator") {
        Vec4 a{1, 2, 3, 4};
        Vec4 b{5, 6, 7, 8};
        auto c = a + b;
        FR_REQUIRE(Eql(c, {6, 8, 10, 12}));
    };

    FR_STAGE("Minus Operator") {
        Vec4 a{1, 2, 3, 4};
        Vec4 b{5, 6, 7, 8};
        auto c = a - b;
        FR_REQUIRE(Eql(c, {-4, -4, -4, -4}));
    };

    FR_STAGE("Multiplication Operator") {
        Vec4 a{1, 2, 3, 4};
        auto b = a * 3;
        FR_REQUIRE(Eql(b, {3, 6, 9, 12}));
    };

    FR_STAGE("Division Operator") {
        Vec4 a{1, 2, 3, 4};
        auto b = a / 3;
        FR_REQUIRE(Eql(b, {0.33333f, 0.66666f, 0.99999f, 1.33333f}, 0.0001f));
    };

    FR_STAGE("Plus Assign Operator") {
        Vec4 a{1, 2, 3, 4};
        Vec4 b{5, 6, 7, 8};
        b += a;
        FR_REQUIRE(Eql(b, {6, 8, 10, 12}));
    };

    FR_STAGE("Minus Assign Operator") {
        Vec4 a{1, 2, 3, 4};
        Vec4 b{5, 6, 7, 8};
        b -= a;
        FR_REQUIRE(Eql(b, {4, 4, 4, 4}));
    };

    FR_STAGE("Times Assign Operator") {
        Vec4 a{1, 2, 3, 4};
        a *= 3;
        FR_REQUIRE(Eql(a, {3, 6, 9, 12}));
    };

    FR_STAGE("Divide Assign Operator") {
        Vec4 a{1, 2, 3, 4};
        a /= 3;
        FR_REQUIRE(Eql(a, {0.33333f, 0.66666f, 0.99999f, 1.33333f}, 0.0001f));
    };

    FR_STAGE("Length") {
        fr::Vec4 a{2, 2, 2, 2};
        FR_REQUIRE(Eql(a.getLength(), 4));
    };

    FR_STAGE("Normalized") {
        Vec4 a{1, 2, 3, 4};
        auto b = a.getNormalized();
        FR_REQUIRE(Eql(b, {0.18257f, 0.36515f, 0.54772f, 0.73010f}, 0.001f));
    };

    FR_STAGE("Normalize") {
        Vec4 a{1, 1, 1, 1};
        a.normalize();
        FR_REQUIRE(Eql(a, {0.5f, 0.5f, 0.5f, 0.5f}));
    };

    FR_STAGE("Dot Zero") {
        Vec4 a;
        Vec4 b;
        FR_REQUIRE(Eql(a.dot(b), 0));
    };

    FR_STAGE("Dot Non-Zero") {
        Vec4 a{1, 2, 3, 4};
        Vec4 b{5, 6, 7, 8};
        FR_REQUIRE(Eql(a.dot(b), 70));
    };
};