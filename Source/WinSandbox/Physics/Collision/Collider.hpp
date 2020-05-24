#pragma once
#include <Freight/Math.hpp>
class Rigidbody;

struct Collider
{
    std::shared_ptr<Rigidbody> body;

    enum class Type {
        HALF_SPACE,
        SPHERE,
        BOX,
    };

    virtual Type getType() const = 0;
};

struct SphereCollider : public Collider
{
    fr::Vec3 position;
    fr::Real radius;

    inline virtual Type getType() const { return Type::SPHERE; }
};

struct HalfSpace : public Collider
{
    fr::Vec3 normal;
    fr::Real offset;

    inline virtual Type getType() const { return Type::HALF_SPACE; }
};

struct BoxCollider : public Collider
{
    fr::Vec3 halfSizes;
    fr::Transform offset;

    inline virtual Type getType() const { return Type::BOX; }
};