#pragma once
#include "Freight.hpp"
#include "Freight/Math.hpp"
#include "LoadEvents.hpp"

class PhysicsSystem
{
private:

    struct Entity
    {
        EntID parent;
        fr::Transform transform;
    };

    struct OBB
    {
        EntID entity;
        fr::Transform transform;
    };

public:

    PhysicsSystem();
    ~PhysicsSystem();

    void start();
    void update();
    void stop();

private:

    bool isColliding(const OBB &a, const OBB &b);

private:

    std::vector<OBB> mOBBs;
    std::unordered_map<EntID, Entity> mEntities;

};