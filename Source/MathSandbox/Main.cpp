#include <Freight.hpp>
#include <Freight/Math.hpp>
using namespace fr;

int main() {

    Vec3 normal = Normal(Vec3{1, 1, 1});

    const Vec3 &xAxis {normal};
    Vec3 yAxis, zAxis;

    const Real s = (Real)1 / std::sqrt(xAxis[2] * xAxis[2] + xAxis[0] * xAxis[0]);

    yAxis = {xAxis[2]*s, 0, -xAxis[0]*s};
    zAxis = {xAxis[1] * yAxis[0], xAxis[2] * yAxis[0] - xAxis[0] * yAxis[2], -xAxis[1] * yAxis[0]};

    FR_LOG("Normal: " << normal);
    FR_LOG("X Axis: " << xAxis);
    FR_LOG("Y Axis: " << yAxis);
    FR_LOG("Z Axis: " << zAxis);
    FR_LOG("X Axis Len: " << xAxis.getLength());
    FR_LOG("Y Axis Len: " << yAxis.getLength());
    FR_LOG("Z Axis Len: " << zAxis.getLength());

    return 0;
}