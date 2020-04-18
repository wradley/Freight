#include "Particle.hpp"

Particle::Particle() :
    acceleration(),
    velocity(),
    position(),
    forces(),
    damping(0.3),
    iMass(1)
{}


Particle::~Particle()
{}


void Particle::applyForce(const fr::Vec3 &force)
{
    forces += force;
}


void Particle::integrate(fr::Real dt)
{
    if (dt <= 0.0) return;

    position += velocity * dt;

    forces += {0, -9.8, 0};
    fr::Vec3 aPrime = acceleration + forces * iMass;

    velocity += aPrime * dt;
    velocity *= pow(damping, dt);

    forces = {0,0,0};
}
