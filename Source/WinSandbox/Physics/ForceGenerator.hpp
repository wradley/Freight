#pragma once
#include <Freight/Math.hpp>
#include "Rigidbody.hpp"

class ForceGenerator
{
public:

    virtual void updateForce(Rigidbody *rb, fr::Real dt) = 0;
};


class Spring : public ForceGenerator
{
public:

    Spring();
    ~Spring();

    virtual void updateForce(Rigidbody *rb, fr::Real dt) override;

    // point in rigidbody local space
    fr::Vec3 localConnectionPt;

    // point in world the other end of the spring is connected to
    fr::Vec3 otherConnectionPt;

    fr::Real springConstant;
    fr::Real restLength;
};