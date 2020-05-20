#pragma once
#include <Freight.hpp>
#include <Freight/Math.hpp>
class Rigidbody;

struct Contact
{
    // bodies involved in contact. One can be null for immovable objects
    std::shared_ptr<Rigidbody> bodies[2];

    fr::Real restitution;
    fr::Real friction;

    // point of contact in world space
    fr::Vec3 point;

    // direction of contact in world space
    fr::Vec3 normal;

    // depth of contact from contact point
    fr::Real depth;

    // from contact space to world space
    fr::Mat3 toWorld;

    // closing velocity at point of contact
    fr::Vec3 velocity;

    // required change in velocity for contact to be resolved
    fr::Real goalDeltaVelocity;

    // world-space position of contact point relative to each body
    fr::Vec3 relativeContactPosition[2];

    // calculates the toWorld matrix
    void calculateContactBasisMatrix(fr::Mat3 &m) const;

    fr::Vec3 calculateLocalVelocity(unsigned int bodyIndex, fr::Real dt) const;

    void calculateGoalDeltaVelocity(fr::Real dt, fr::Real velocityEpsilon);

    void applyPositionChange(fr::Vec3 dLinear[2], fr::Vec3 dAngular[2], fr::Real depth) const;
    void applyVelocityChange(fr::Vec3 dVel[2], fr::Vec3 dRot[2]);

    // calculate contact data
    void calculateContactData(fr::Real dt, fr::Real velocityEpsilon);

    fr::Vec3 calculateFrictionImpulse(fr::Mat3 inverseInertiaTensor[2]) const;
    fr::Vec3 calculateFrictionlessImpulse(fr::Mat3 inverseInertiaTensor[2]) const;
};


class ContactResolver
{
public:

    ContactResolver(
        fr::uint positionResolutionIterations,
        fr::uint velocityResolutionIterations,
        fr::Real penetrationEpsilon = 0.0001f,
        fr::Real velocityEpsilon = 0.0001f
    );

    void setIterations(size_t i);
    void resolveContacts(std::vector<Contact> &contacts, fr::Real dt);

private:

    void prepareContacts(std::vector<Contact> &contacts, fr::Real dt);
    void adjustPositions(std::vector<Contact> &contacts, fr::Real dt);
    void adjustVelocities(std::vector<Contact> &contacts, fr::Real dt);

private:

    fr::uint mPositionIterations;
    fr::uint mVelocityIterations;

    // penetration depths less than epsilon will be ignored for stability
    const fr::Real mPenetrationEpsilon;

    // velocities less than epsilon will be ignored for stability
    const fr::Real mVelocityEpsilon;
};