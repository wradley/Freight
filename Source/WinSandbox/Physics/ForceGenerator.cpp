#include "ForceGenerator.hpp"


void Spring::updateForce(Rigidbody *rb, fr::Real dt)
{
    // get rb connection point in world space
    fr::Vec3 rbConnectionPt = rb->localPointToWorld(localConnectionPt);

    // calculate force
    fr::Vec3 force = rbConnectionPt - otherConnectionPt;
    fr::Real magnitude = abs(force.getLength() - restLength) * springConstant;
    force = force.getNormalized() * -magnitude;

    rb->addForceAtWorldPoint(force, rbConnectionPt);
}
