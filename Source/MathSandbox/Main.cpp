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

    const fr::Vec3 &xAxis = normal;

    fr::Vec3 tmp{1, 0, 0};

    // pointing closer to world x axis than world y axis (use world y)
    if (std::abs(xAxis[0]) > std::abs(xAxis[1])) tmp = {0, 1, 0};

    const fr::Vec3 zAxis = fr::Normal(fr::RHCross(xAxis, tmp));
    const fr::Vec3 yAxis = fr::Normal(fr::RHCross(zAxis, xAxis));

    FR_LOG("X Axis: " << xAxis);
    FR_LOG("t Axis: " << tmp);
    FR_LOG("Z Axis: " << zAxis);
    FR_LOG("Y Axis: " << yAxis);
    FR_LOG("X Axis Len: " << xAxis.getLength());
    FR_LOG("Y Axis Len: " << yAxis.getLength());
    FR_LOG("Z Axis Len: " << zAxis.getLength());

    return 0;
}