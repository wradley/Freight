#pragma once
#include <Freight/Math.hpp>

class Rigidbody
{
public:

    Rigidbody(
        const fr::Vec3 &position, 
        const fr::Vec3 &velocity, 
        fr::Real inverseMass,
        const fr::Quat &orientation,
        const fr::Vec3 &rotation,
        const fr::Mat3 &inverseTensorMat
    );
    ~Rigidbody();

    fr::Vec3 getPosition() const;
    void setPosition(const fr::Vec3 &position);
    fr::Vec3 getVelocity() const;
    void setVelocity(const fr::Vec3 &velocity);
    fr::Vec3 getInverseMass() const;
    void setInverseMass(fr::Real inverseMass);

    fr::Quat getOrientation() const;
    void setOrientation(const fr::Quat &orientation);
    fr::Vec3 getRotation() const;
    void setRotation(const fr::Vec3 &rotation);

    void addForce(const fr::Vec3 &force);
    void addForceAtWorldPoint(const fr::Vec3 &worldforce, const fr::Vec3 &worldpoint);
    void addForceAtLocalPoint(const fr::Vec3 &worldforce, const fr::Vec3 &localpoint);

    void integrate(fr::Real deltaTime);

    fr::Vec3 localPointToWorld(const fr::Vec3 &pt) const;

    fr::Mat4 getTransformMatrix() const;

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