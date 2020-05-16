#pragma once
#include "Freight/pch.hpp"
#include "Freight/Math.hpp"
#include "ForceGenerator.hpp"
#include "json.hpp"
#include "Freight.hpp"
#include "Collision/Contact.hpp"
#include "../LoadEvents.hpp"
class Collider;

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
    void addColliderComponent(std::shared_ptr<const AddColliderComponentEvent> e);

private:

    struct Entity
    {
        fr::EntID parent;
        fr::Transform transform;
        std::shared_ptr<Rigidbody> rigidbody;
    };

    fr::Mat4 GetWorldTransform(fr::EntID id);
    void ToWorld(fr::EntID ent, fr::Vec3 &position, fr::Quat &orientation);
    void ToLocal(fr::EntID ent, fr::Vec3 &position, fr::Quat &orientation);

    ContactResolver mContactResolver;

    std::unordered_map<fr::EntID, Entity> mEntities;

    std::vector<std::tuple<fr::EntID, ForceGenerator*>> mForceGenerators;
    std::vector<std::unique_ptr<Collider>> mColliders;

    fr::HandlerMask mHandlerMask;


    // todo: remove
    bool mTestingForce = false;
};