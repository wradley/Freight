#pragma once
#include <Freight/Math.hpp>

struct Collider
{
    fr::Vec3 position;
};

struct SphereCollider : public Collider
{
    fr::Real radius;
};

struct PlaneCollider : public Collider
{
    fr::Vec3 normal;
    fr::Real offset;
};