#include "CollisionDetector.hpp"
#include "../Rigidbody.hpp"


void CollisionDetector::Detect(const Collider *a, const Collider *b, std::vector<Contact> &contacts)
{
    switch (a->getType())
    {
    case Collider::Type::HALF_SPACE:
        switch (b->getType())
        {
        case Collider::Type::HALF_SPACE:
            FR_LOG("todo?");
            break;
        case Collider::Type::SPHERE:
            SphereHalfSpace(*(const SphereCollider *)b, *(const HalfSpace *)a, contacts);
            break;
        default:
            FR_CRASH("Should not be here");
            break;
        }
        break;
    case Collider::Type::SPHERE:
        switch (b->getType())
        {
        case Collider::Type::HALF_SPACE:
            SphereHalfSpace(*(const SphereCollider *)a, *(const HalfSpace *)b, contacts);
            break;
        case Collider::Type::SPHERE:
            SphereSphere(*(const SphereCollider *)b, *(const SphereCollider *)a, contacts);
            break;
        default:
            FR_CRASH("Should not be here");
            break;
        }
        break;
    default:
        FR_CRASH("Shoud not be here");
        break;
    }
}


void CollisionDetector::SphereSphere(const SphereCollider &a, const SphereCollider &b, std::vector<Contact> &contacts)
{
    auto A = a.body->getTransformMatrix();
    auto B = b.body->getTransformMatrix();
    fr::Vec3 aPos = A * fr::Vec4{a.position[0], a.position[1], a.position[2], 1}; // todo simplify vec3 multiplication
    fr::Vec3 bPos = B * fr::Vec4{b.position[0], b.position[1], b.position[2], 1};

    auto diff = aPos - bPos;
    auto dist = fr::Len(diff);
    if (dist <= (fr::Real)0 || dist >= a.radius + b.radius)
        return;

    Contact contact;
    contact.point = aPos + diff / 2;
    contact.normal = diff / dist;
    contact.depth = a.radius + b.radius - dist;
    contact.bodies[0] = a.body;
    contact.bodies[1] = b.body;
    contact.restitution = 1.0f;
    contact.friction = 0.9f;
    contacts.push_back(contact);
}


void CollisionDetector::SphereHalfSpace(const SphereCollider &s, const HalfSpace &h, std::vector<Contact> &contacts)
{
    auto S = s.body->getTransformMatrix();
    auto H = h.body->getTransformMatrix();
    fr::Vec3 sPos = S * fr::Vec4{s.position[0], s.position[1], s.position[2], 1};
    fr::Vec3 hNorm = fr::Normal(fr::Vec3(H * fr::Vec4{h.normal[0], h.normal[1], h.normal[2], 1}));
    auto scaled = h.normal * h.offset;
    fr::Real hOffset = fr::Len(fr::Vec3(H * fr::Vec4{scaled[0], scaled[1], scaled[2], 1}));

    auto dist = fr::Dot(sPos, hNorm) - hOffset - s.radius;
    if (dist >= 0) return;

    Contact contact;
    contact.point = sPos - hNorm * (dist + s.radius);
    contact.normal = hNorm;
    contact.depth = -dist;
    contact.bodies[0] = s.body;
    contact.bodies[1] = h.body;
    contact.restitution = 0.9f;
    contact.friction = 0.9f;
    contacts.push_back(contact);
}
