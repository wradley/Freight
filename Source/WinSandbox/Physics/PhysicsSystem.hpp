#pragma once
#include "Freight.hpp"
#include "Freight/Math.hpp"
#include "ParticleForceManager.hpp"

class PhysicsSystem
{
private:

    struct Entity
    {
        fr::EntID parent;
        fr::Transform transform;
    };

    struct ParticleWrapper
    {
        fr::EntID entity;
        Particle *particle;
    };

public:

    PhysicsSystem();
    ~PhysicsSystem();

    void start();
    void update(fr::Real deltaTime);
    void stop();

private:

    fr::Mat4 getGlobalTransform(fr::EntID e);
    fr::Vec3 getGlobalPosition(fr::EntID e);

private:

    ParticleForceManager mForceManager;
    std::unordered_map<fr::EntID, Entity> mEntities;
    std::vector<ParticleWrapper> mParticles;

};