#pragma once
#include "Freight/pch.hpp"
#include "Freight/Math.hpp"
#include "ForceGenerator.hpp"
#include "json.hpp"
#include "Freight.hpp"

class PhysicsSystem
{
public:

    PhysicsSystem();
    ~PhysicsSystem();

    void start();
    void update(fr::Real deltaTime);
    void stop();

private:

    void addRigidbodyComponent(fr::EntID ent, const nlohmann::json &data);

private:

    struct Entity
    {
        fr::EntID parent;
        fr::Transform transform;
        Rigidbody *rigidbody;
    };

    fr::Mat4 GetWorldTransform(fr::EntID id);
    void ToWorld(fr::EntID ent, fr::Vec3 &position, fr::Quat &orientation);
    void ToLocal(fr::EntID ent, fr::Vec3 &position, fr::Quat &orientation);

    std::unordered_map<fr::EntID, Entity> mEntities;

    std::vector<std::tuple<fr::EntID, ForceGenerator*>> mForceGenerators;
    //std::vector<Rigidbody*> mRigidbodies;

    fr::HandlerMask mHandlerMask;
};