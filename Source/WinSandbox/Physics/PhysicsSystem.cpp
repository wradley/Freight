#include "PhysicsSystem.hpp"
#include "../LoadEvents.hpp"
#include "Collision/Collider.hpp"
#include "Collision/CollisionDetector.hpp"

PhysicsSystem::PhysicsSystem() : mContactResolver(1000, 1000)
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

    em.on<AddColliderComponentEvent>([this](std::shared_ptr<const AddColliderComponentEvent> e) {
        addColliderComponent(e);
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
                if (key.openglAction == 1) {
                    mTestingForce = true;
                    //FR_LOG("Press");
                }
                else if (key.openglAction == 0) {
                    mTestingForce = false;
                    //FR_LOG("Release");
                }
            }
        }
    });
}


void PhysicsSystem::update(fr::Real dt)
{
    /*if (mEntities.find(8) != mEntities.end()) {
        static bool firstTime = true;
        if (mTestingForce && firstTime) {
            firstTime = false;
            mEntities[8].rigidbody->addForceAtLocalPoint({0, 0, -500}, {0.0, 0.5, 0.5});
        }
    }*/

    if (!mTestingForce)
        return;

    static bool firstUpdate = true;
    if (firstUpdate) {
        firstUpdate = false;
        if (mEntities.find(8) != mEntities.end()) {
            mEntities[8].rigidbody->setRotation({fr::ToRad(-360), 1, 0});
            mEntities[8].rigidbody->setVelocity({0, 0, -1});
        }
    }

    static fr::Real testTotalTime = 0;
    if (mEntities.find(8) != mEntities.end()) {
        testTotalTime += dt;
        //FR_LOG(testTotalTime << "," << mEntities[8].transform.position[0] << "," << mEntities[8].transform.position[1] << "," << mEntities[8].transform.position[2]);
    }


    // update forces
    for (auto &[eID, fg] : mForceGenerators) {
        auto &ent = mEntities[eID];
        fg->updateForce(ent.rigidbody.get(), dt);
    }

    // integrate
    // todo: optimize? only update active entities (std::vector<EntID> activeEntities)
    for (auto &pair : mEntities) {
        auto &ent = pair.second;
        if (!ent.rigidbody) continue;

        ent.rigidbody->integrate(dt);

        ent.transform.position = ent.rigidbody->getPosition();
        ent.transform.rotation = ent.rigidbody->getOrientation();
    }

    // contact detection
    std::vector<Contact> contacts;
    for (size_t i = 0; i < mColliders.size() - 1; ++i) {
        for (size_t j = i + 1; j < mColliders.size(); ++j) {
            CollisionDetector::Detect(mColliders[i].get(), mColliders[j].get(), contacts);
        }
    }

    // contact resolution
    mContactResolver.setIterations(contacts.size() * 4);
    mContactResolver.resolveContacts(contacts, dt);

    // update rest of engine
    auto te = new TransformEntitiesEvent;
    for (auto &pair : mEntities) {
        auto &ent = pair.second;
        if (!ent.rigidbody) continue;

        TransformEntitiesEvent::EntityTransform et;
        et.entity = pair.first;
        et.transform = ent.transform;
        te->transforms.push_back(et);
    }
    fr::EventManager::Instance().post<TransformEntitiesEvent>(std::shared_ptr<TransformEntitiesEvent>(te), mHandlerMask);
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

    mEntities[ent].rigidbody = std::shared_ptr<Rigidbody>(rb);
}


void PhysicsSystem::addColliderComponent(std::shared_ptr<const AddColliderComponentEvent> e)
{
    FR_ASSERT(mEntities.find(e->entity) != mEntities.end(), "Ent [" << e->entity << "] does not exist");
    FR_ASSERT(mEntities[e->entity].rigidbody, "Ent [" << e->entity << "] does not have a rigidbody");

    switch (e->type)
    {
    case AddColliderComponentEvent::ColliderType::HALF_SPACE: {
        auto collider = new HalfSpace;
        collider->body = mEntities[e->entity].rigidbody;
        collider->normal = e->normal;
        collider->offset = e->offset.position.getLength();
        mColliders.push_back(std::unique_ptr<Collider>(collider));
    } break;
    case AddColliderComponentEvent::ColliderType::SPHERE: {
        auto collider = new SphereCollider;
        collider->body = mEntities[e->entity].rigidbody;
        collider->position = e->offset.position;
        collider->radius = e->radius;
        mColliders.push_back(std::unique_ptr<Collider>(collider));
    } break;
    case AddColliderComponentEvent::ColliderType::BOX: {
        auto collider = new BoxCollider;
        collider->body = mEntities[e->entity].rigidbody;
        collider->offset = e->offset;
        collider->halfSizes = e->halfSizes;
        mColliders.push_back(std::unique_ptr<Collider>(collider));
    } break;
    default:
        FR_CRASH("todo");
        break;
    }
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
