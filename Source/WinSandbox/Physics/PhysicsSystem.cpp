#include "PhysicsSystem.hpp"
#include "../LoadEvents.hpp"


PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}


void PhysicsSystem::start()
{
    auto &em = fr::EventManager::Instance();
    em.on<AddEntityEvent>([this](std::shared_ptr<const AddEntityEvent> e) {
        mEntities[e->entity].parent = e->parent;
        mEntities[e->entity].transform = e->transform;
    });

    em.on<AddParticleComponentEvent>([this](std::shared_ptr<const AddParticleComponentEvent> e) {
        ParticleWrapper pw;
        pw.entity = e->entity;
        pw.particle = new Particle;
        pw.particle->iMass = e->inverseMass;
        for (auto &generator : e->addForceGenerators.generators) {
            switch (generator.type)
            {
            case AddParticleForceGeneratorsEvent::SPRING_GENERATOR:
                for (auto &source : mParticles) { // find source
                    if (source.entity == generator.spring.source) {
                        auto psg = new ParticleSpringGenerator(source.particle, generator.spring.springConstant, generator.spring.restLength);
                        mForceManager.addGenerator(psg, pw.particle);
                    }
                }
                break;
            default:
                break;
            }
        }
        mParticles.push_back(pw);
    });
}


void PhysicsSystem::update(fr::Real dt)
{
    // get global positions for each particle
    for (auto &[ent, p] : mParticles)
        p->position = getGlobalPosition(ent);

    // apply forces & integrate
    mForceManager.update(dt);

    // update entities
    auto tee = new TransformEntitiesEvent;
    for (auto &[ent, p] : mParticles) {

        const fr::Real BOX_BOUNDS = 10;
        if (p->position[0] > BOX_BOUNDS)  p->position[0] = -BOX_BOUNDS;
        if (p->position[0] < -BOX_BOUNDS) p->position[0] = BOX_BOUNDS;
        if (p->position[1] > BOX_BOUNDS)  p->position[1] = -BOX_BOUNDS;
        if (p->position[1] < -BOX_BOUNDS) p->position[1] = BOX_BOUNDS;
        if (p->position[2] > BOX_BOUNDS)  p->position[2] = -BOX_BOUNDS;
        if (p->position[2] < -BOX_BOUNDS) p->position[2] = BOX_BOUNDS;

        mEntities[ent].transform.position = p->position;

        TransformEntitiesEvent::EntityTransform et;
        et.entity = ent;
        et.transform.position = p->position;
        tee->transforms.push_back(et);
    }

    fr::EventManager::Instance().post(std::shared_ptr<const TransformEntitiesEvent>(tee));
}


void PhysicsSystem::stop()
{
    mForceManager.removeAllGenerators();
    for (auto &[ent, p] : mParticles) {
        if (ent && p) delete p;
    }
}


fr::Mat4 PhysicsSystem::getGlobalTransform(fr::EntID e)
{
    if (mEntities.find(e) == mEntities.end()) return fr::Mat4();
    if (mEntities[e].parent == e) return mEntities[e].transform.getMat();
    return getGlobalTransform(mEntities[e].parent) * mEntities[e].transform.getMat();
}


fr::Vec3 PhysicsSystem::getGlobalPosition(fr::EntID e)
{
    return getGlobalTransform(e) * fr::Vec4({0, 0, 0, 1});
}

