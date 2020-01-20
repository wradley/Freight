#include "PhysicsSystem3D.hpp"


PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}


void PhysicsSystem::start()
{
    auto &em = fr::EventManager::Instance();
    em.on<LoadEntityEvent>([this](std::shared_ptr<const LoadEntityEvent> e) {
        mEntities[e->entity].parent = e->parent;
        mEntities[e->entity].transform = e->transform;
    });

    em.on<LoadColliderComponentEvent>([this](std::shared_ptr<const LoadColliderComponentEvent> e) {
        if (e->type == LoadColliderComponentEvent::ColliderType::BOX) {
            OBB obb;
            obb.entity = e->entity;
            obb.transform = e->transform;
            mOBBs.push_back(obb);
        }
    });
}


void PhysicsSystem::update()
{
    for (auto &a : mOBBs) {
        for (auto &b : mOBBs) {
            if (&a == &b) continue;
            if (isColliding(a, b)) {
                auto ce = new CollisionEvent;
                ce->a = a.entity;
                ce->b = b.entity;
                fr::EventManager::Instance().post(std::shared_ptr<const CollisionEvent>(ce));
            }
        }
    }
}


void PhysicsSystem::stop()
{
}


bool PhysicsSystem::isColliding(const OBB &a, const OBB &b)
{
    return false;
}
