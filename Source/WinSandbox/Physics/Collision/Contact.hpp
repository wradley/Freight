#pragma once
#include <Freight/Math.hpp>

struct Contact
{
    // point of contact in world space
    fr::Vec3 point;

    // direction of contact in world space
    fr::Vec3 normal;

    // depth of contact from contact point
    fr::Real depth;

    // from contact space to world space
    fr::Mat3 toWorld;

    // calculates the toWorld matrix
    void calculateContactBasis();
}; 