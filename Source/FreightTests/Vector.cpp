#include <Freight/Testing.hpp>
#include "../Freight/Math/Vector.hpp"

FR_TEST("Vector 2")
{
    FR_STAGE("Zero Constructor") {
        fr::Vec2 a;
        FR_REQUIRE(a[0] == 0.0f && a[1] == 0.0f);
    }

    FR_STAGE("Non-Zero Constructor") {
        fr::Vec2 a({1, 2});
        FR_REQUIRE(a[0] == 1.0f && a[1] == 2.0f);
    }
};