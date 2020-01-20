#pragma once
#include <Freight/Math.hpp>

class Rigidbody
{
public:

    Rigidbody();
    ~Rigidbody();

    void setPosition(const fr::Vec3 &position);
    void setVelocity(const fr::Vec3 &velocity);
    void setInverseMass(fr::Real inverseMass);

    void setOrientation(const fr::Quat &orientation);
    void setRotation(const fr::Vec3 &rotation);

    void addForce(const fr::Vec3 &force);
    void addForceAtWorldPoint(const fr::Vec3 &worldforce, const fr::Vec3 &worldpoint);
    void addForceAtLocalPoint(const fr::Vec3 &worldforce, const fr::Vec3 &localpoint);

    void integrate(fr::Real deltaTime);

    fr::Vec3 localPointToWorld(const fr::Vec3 &pt) const;

private:

    void calculateCachedValues();

private:

    // linear
    fr::Vec3 mPosition;
    fr::Vec3 mVelocity;
    fr::Real mInverseMass;
    fr::Vec3 mAccumulatedForce;
    fr::Real mLinearDamping;

    // angular
    fr::Quat mOrientation;
    fr::Vec3 mRotation;
    fr::Mat3 mInverseTensorMat;
    fr::Vec3 mAccumulatedTorque;
    fr::Real mAngularDamping;

    struct {
        fr::Mat4 transformMatrix; // todo: 4x3?
        fr::Mat3 inverseTensorMatWorld;
    } mCache;
};