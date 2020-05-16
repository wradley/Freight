#include <Freight.hpp>
#include <Freight/Math.hpp>
using namespace fr;

int main() {

    const Vec3 normal = Normal(Vec3{3, 4, 1});

    /*
    const Vec3 &xAxis {normal};
    Vec3 yAxis, zAxis;

    const Real s = (Real)1 / std::sqrt(xAxis[2] * xAxis[2] + xAxis[0] * xAxis[0]);

    yAxis = {xAxis[2]*s, 0, -xAxis[0]*s};
    zAxis = {xAxis[1] * yAxis[0], xAxis[2] * yAxis[0] - xAxis[0] * yAxis[2], -xAxis[1] * yAxis[0]};
    //FR_LOG(zAxis);
    //zAxis = RHCross(xAxis, yAxis);
    //FR_LOG(zAxis);
    */

    fr::Vec3 a{1, 2, 3};
    fr::Vec3 b{4, 5, 6};
    fr::Mat3 A = fr::SkewSymmetric(a);

    auto ab = fr::RHCross(a, b);
    auto Ab = A * b;

    return 0;
}