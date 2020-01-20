#pragma once
#include "Freight/pch.hpp"
#include "Freight/Math.hpp"
#include "ForceGenerator.hpp"

class PhysicsSystem
{
public:

    PhysicsSystem();
    ~PhysicsSystem();

    void start();
    void update(fr::Real deltaTime);
    void stop();

private:

    struct Entity
    {
        fr::EntID parent;
        fr::Transform transform;

        fr::Mat4 getWorldTransformMat();
    };

    std::unordered_map<fr::EntID, Entity> mEntities;

    std::vector<ForceGenerator*> mForceGenerators;

};