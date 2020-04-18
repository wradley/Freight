#include "Rigidbody.hpp"
#include <Freight/pch.hpp>

Rigidbody::Rigidbody(
    const fr::Vec3 &position,
    const fr::Vec3 &velocity,
    fr::Real inverseMass,
    const fr::Quat &orientation,
    const fr::Vec3 &rotation,
    const fr::Mat3 &inverseTensorMat
) : mPosition(position),
    mVelocity(velocity),
    mInverseMass(inverseMass),
    mAccumulatedForce(),
    mLinearDamping(0.9),
    mOrientation(orientation),
    mRotation(rotation),
    mInverseTensorMat(inverseTensorMat),
    mAccumulatedTorque(),
    mAngularDamping(0.9)
{
}


Rigidbody::~Rigidbody()
{
}


fr::Vec3 Rigidbody::getPosition() const
{
    return mPosition;
}


void Rigidbody::setPosition(const fr::Vec3 &position)
{
    mPosition = position;
}


fr::Vec3 Rigidbody::getVelocity() const
{
    return mVelocity;
}


void Rigidbody::setVelocity(const fr::Vec3 &velocity)
{
    mVelocity = velocity;
}


fr::Real Rigidbody::getInverseMass() const
{
    return mInverseMass;
}


void Rigidbody::setInverseMass(fr::Real inverseMass)
{
    mInverseMass = inverseMass;
}


fr::Quat Rigidbody::getOrientation() const
{
    return mOrientation;
}


void Rigidbody::setOrientation(const fr::Quat &orientation)
{
    mOrientation = orientation;
}


fr::Vec3 Rigidbody::getRotation() const
{
    return mRotation;
}


void Rigidbody::setRotation(const fr::Vec3 &rotation)
{
    mRotation = rotation;
}


void Rigidbody::addForce(const fr::Vec3 &force)
{
    mAccumulatedForce += force;
}


void Rigidbody::addForceAtWorldPoint(const fr::Vec3 &force, const fr::Vec3 &point)
{
    // convert so relative to center of mass
    fr::Vec3 pt = point - mPosition;

    //mAccumulatedForce += force;
    mAccumulatedTorque += fr::RHCross(pt, force);
}


void Rigidbody::addForceAtLocalPoint(const fr::Vec3 &force, const fr::Vec3 &point)
{
    // todo: is this a frame behind now?
    fr::Vec3 pt = mCache.transformMatrix * fr::Vec4({point[0], point[1], point[2], 1});
    addForceAtWorldPoint(force, pt);
}


void Rigidbody::integrate(fr::Real dt)
{
    fr::Vec3 angularAccel = mCache.inverseTensorMatWorld * mAccumulatedTorque;
    fr::Vec3 linearAccel = mAccumulatedForce * mInverseMass;

    mRotation += angularAccel * dt;
    mVelocity += linearAccel * dt;

    mRotation *= pow(mAngularDamping, dt);
    mVelocity *= pow(mLinearDamping, dt);

    mOrientation += mRotation * dt;;
    mPosition += mVelocity * dt;

    mAccumulatedForce = {0,0,0};
    mAccumulatedTorque = {0,0,0};

    calculateCachedValues();
}


fr::Vec3 Rigidbody::localPointToWorld(const fr::Vec3 &pt) const
{
    return mCache.transformMatrix * fr::Vec4({pt.at(0), pt.at(0), pt.at(0), (fr::Real)1.0});
}


fr::Mat4 Rigidbody::getTransformMatrix() const
{
    return mCache.transformMatrix;
}


void Rigidbody::calculateCachedValues()
{
    mOrientation.normalize();

    // todo: optimize
    mCache.transformMatrix = fr::Translate(mPosition) * fr::ToMat4(mOrientation);

    // todo: optimize
    auto orientation = fr::ToMat3(mOrientation);
    mCache.inverseTensorMatWorld = orientation * mInverseTensorMat * fr::Inverse(orientation);
}
