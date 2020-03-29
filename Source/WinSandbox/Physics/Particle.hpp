#pragma once
#include "Freight/Math.hpp"

class Particle
{
public:

    Particle();
    ~Particle();

    void applyForce(const fr::Vec3 &force);
    void integrate(fr::Real dt);

public:

    fr::Vec3 acceleration;
    fr::Vec3 velocity;
    fr::Vec3 position;
    fr::Vec3 forces;
    fr::Real damping; // 0.0 = no movement, 1.0 = no drag
    fr::Real iMass; // inverse mass ie. 1/mass
};


class ParticleForceGenerator
{
public:

    virtual inline ~ParticleForceGenerator() {}

    virtual void update(Particle *p, fr::Real deltaTime) = 0;
    virtual bool isFinished() const = 0;
};


class ParticleGravityGenerator : public ParticleForceGenerator
{
public:

    ParticleGravityGenerator() {}
    ~ParticleGravityGenerator() {}

    inline void update(Particle *p, fr::Real dt) override {
        p->applyForce({0,-9.8,0});
    }

    bool isFinished() const override {
        return false;
    }
};


class ParticleSpringGenerator : public ParticleForceGenerator
{
public:

    ParticleSpringGenerator(const Particle *Other, fr::Real SpringConstant, fr::Real RestLength) : 
        other(Other), springConstant(SpringConstant), restLength(RestLength) {}
    ~ParticleSpringGenerator() {}

    const Particle *other;
    fr::Real springConstant;
    fr::Real restLength;

    inline void update(Particle *p, fr::Real dt) override {
        fr::Vec3 dir = p->position - other->position;
        fr::Real mag = abs(dir.getLength() - restLength) * springConstant;
        dir.normalize();
        p->applyForce(dir * -mag);
    }

    bool isFinished() const override {
        return false;
    }
};