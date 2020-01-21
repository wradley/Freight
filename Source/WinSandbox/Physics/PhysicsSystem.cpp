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

    mHandlerMask = em.GenMask();

    em.on<AddEntityEvent>([this](std::shared_ptr<const AddEntityEvent> e) {
        mEntities[e->entity].parent = e->parent;
        mEntities[e->entity].transform = e->transform;
        mEntities[e->entity].rigidbody = nullptr;
    });

    em.on<AddParticleComponentEvent>([this](std::shared_ptr<const AddParticleComponentEvent> e) {
        //ParticleWrapper pw;
        //pw.entity = e->entity;
        //pw.particle = new Particle;
        //pw.particle->iMass = e->inverseMass;
        //for (auto &generator : e->addForceGenerators.generators) {
        //    switch (generator.type)
        //    {
        //    case AddParticleForceGeneratorsEvent::SPRING_GENERATOR:
        //        for (auto &source : mParticles) { // find source
        //            if (source.entity == generator.spring.source) {
        //                auto psg = new ParticleSpringGenerator(source.particle, generator.spring.springConstant, generator.spring.restLength);
        //                mForceManager.addGenerator(psg, pw.particle);
        //            }
        //        }
        //        break;
        //    default:
        //        break;
        //    }
        //}
        //mParticles.push_back(pw);
    });

    em.on<AddComponentEvent>([this](std::shared_ptr<const AddComponentEvent> e) {
        if (e->type == "rigidbody") addRigidbodyComponent(e->entity, e->data);
    });

    em.on<TransformEntitiesEvent>([this](std::shared_ptr<const TransformEntitiesEvent> e) {
        for (auto &tform : e->transforms) {
            if (mEntities.find(tform.entity) == mEntities.end()) continue;
            auto &ent = mEntities[tform.entity];
            if (!ent.rigidbody) continue;
            
            // convert entity positition and orientation from parent space to world space
            auto position = ent.rigidbody->getPosition();
            auto orientation = ent.rigidbody->getOrientation();
            ToWorld(tform.entity, position, orientation);
            ent.rigidbody->setPosition(position);
            ent.rigidbody->setOrientation(orientation);
        }
    }, mHandlerMask);

    em.on<InputEvent>([this](std::shared_ptr<const InputEvent> e) {
        for (auto &key : e->keys) {
            if (key.openglKey == 70) {
                if (mEntities.find(8) == mEntities.end()) {
                    FR_DEBUG_LOG("No entity 8 in physics system");
                    continue;
                }

                mEntities[8].rigidbody->addForceAtLocalPoint({0,0,-10}, {0,-1,0});
            }
        }
    });
}


void PhysicsSystem::update(fr::Real dt)
{
    // update forces
    for (auto &[eID, fg] : mForceGenerators) {
        auto &ent = mEntities[eID];
        fg->updateForce(ent.rigidbody, dt);
    }

    // integrate
    // todo: optimize? only update active entities (std::vector<EntID> activeEntities)
    auto te = new TransformEntitiesEvent;
    for (auto &pair : mEntities) {
        auto &ent = pair.second;
        if (!ent.rigidbody) continue;

        fr::Vec3 oldPosition = ent.rigidbody->getPosition();
        fr::Quat oldOrientation = ent.rigidbody->getOrientation();
        ent.rigidbody->integrate(dt);
        if (oldPosition != ent.rigidbody->getPosition() || oldOrientation != ent.rigidbody->getOrientation()) {
            fr::Vec3 position;
            fr::Quat orientation;

            // convert rigidbody world position/orientation to entity local position/orientation
            auto local = ent.rigidbody->getTransformMatrix();
            position[0] = local[0][3];
            position[1] = local[1][3];
            position[2] = local[2][3];
            orientation = fr::ToQuat(local);

            ent.transform.position = position;
            ent.transform.rotation = orientation;
            TransformEntitiesEvent::EntityTransform et;
            et.entity = pair.first;
            et.transform = ent.transform;
            te->transforms.push_back(et);
        }
        // else remove from active entities? -- could have just not moved that frame?
    }
    if (te->transforms.size()) {
        fr::EventManager::Instance().post<TransformEntitiesEvent>(std::shared_ptr<TransformEntitiesEvent>(te), mHandlerMask);
    }
}


void PhysicsSystem::stop()
{
    //FR_CRASH("todo");
}


static fr::Real GetRealOrZero(const nlohmann::json &data, const std::string &name)
{
    if (data && data.is_number()) {
        return data;
    }

    return 0;
}


static fr::Vec3 GetVec3OrZero(const nlohmann::json &data)
{
    if (data && 
        data[0] && data[0].is_number() &&
        data[1] && data[1].is_number() &&
        data[2] && data[2].is_number()    ){
        return fr::Vec3({data[0], data[1], data[2]});
    }

    return fr::Vec3({0,0,0});
}


static fr::Quat GetQuatOrIdentity(const nlohmann::json &data)
{
    if (data &&
        data[0] && data[0].is_number() &&
        data[1] && data[1].is_number() &&
        data[2] && data[2].is_number() &&
        data[3] && data[3].is_number()    ) {
        return fr::Quat({data[0], data[1], data[2], data[3]});
    }

    return fr::Quat({1,0,0,0});
}


static fr::Mat3 GetMat3OrIdentity(const nlohmann::json &data)
{
    if (data &&
        data[0] && data[0].is_number() &&
        data[1] && data[1].is_number() &&
        data[2] && data[2].is_number() &&
        data[3] && data[3].is_number() &&
        data[4] && data[4].is_number() &&
        data[5] && data[5].is_number() &&
        data[6] && data[6].is_number() &&
        data[7] && data[7].is_number() &&
        data[8] && data[8].is_number()    ) {
        return fr::Mat3({
            {data[0], data[1], data[2]},
            {data[3], data[4], data[5]},
            {data[6], data[7], data[8]}
        });
    }

    return fr::Identity3x3();
}


void PhysicsSystem::addRigidbodyComponent(fr::EntID ent, const nlohmann::json &data)
{
    // make sure entity exists
    if (mEntities.find(ent) == mEntities.end()) {
        FR_ERR("No entity [" << ent << "] exists to add rigid body to");
        return;
    }

    // create rigidbody
    fr::Vec3 position;
    fr::Vec3 velocity = {0,0,0};
    fr::Real inverseMass = data["inverse-mass"];
    fr::Quat orientation;
    fr::Vec3 rotation = {0,0,0};
    auto jsonTMat = data["inverse-inertia-tensor"];
    fr::Mat3 inverseTensorMat({
        {jsonTMat[0], jsonTMat[1], jsonTMat[2]},
        {jsonTMat[3], jsonTMat[4], jsonTMat[5]},
        {jsonTMat[6], jsonTMat[7], jsonTMat[8]},
    });
    ToWorld(ent, position, orientation);
    auto rb = new Rigidbody(
        position,
        velocity,
        inverseMass,
        orientation,
        rotation,
        inverseTensorMat
    );

    mEntities[ent].rigidbody = rb;
}


fr::Mat4 PhysicsSystem::GetWorldTransform(fr::EntID id)
{
    auto &ent = mEntities[id];
    if (ent.parent == id) return ent.transform.getMat();
    else return GetWorldTransform(ent.parent) * ent.transform.getMat();
}


void PhysicsSystem::ToWorld(fr::EntID ent, fr::Vec3 &position, fr::Quat &orientation)
{
    auto t = GetWorldTransform(ent);

    position[0] = t[0][3];
    position[1] = t[1][3];
    position[2] = t[2][3];

    orientation = fr::ToQuat(t);
}


void PhysicsSystem::ToLocal(fr::EntID ent, fr::Vec3 &position, fr::Quat &orientation)
{
    auto t = fr::Inverse(GetWorldTransform(ent));

    position[0] = t[0][3];
    position[1] = t[1][3];
    position[2] = t[2][3];

    orientation = fr::ToQuat(t);
}
