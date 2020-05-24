#include "CollisionDetector.hpp"
#include "../Rigidbody.hpp"


void CollisionDetector::Detect(const Collider *a, const Collider *b, std::vector<Contact> &contacts)
{
    if (a->getType() == Collider::Type::SPHERE)
        SphereSomething((const SphereCollider *)a, b, contacts);
    else if (b->getType() == Collider::Type::SPHERE)
        SphereSomething((const SphereCollider *)b, a, contacts);
    else if (a->getType() == Collider::Type::BOX)
        BoxSomething((const BoxCollider *)a, b, contacts);
    else if (b->getType() == Collider::Type::BOX)
        BoxSomething((const BoxCollider *)b, a, contacts);
}


void CollisionDetector::SphereSomething(const SphereCollider *s, const Collider *c, std::vector<Contact> &contacts)
{
    switch (c->getType())
    {
    case Collider::Type::BOX:
        SphereBox(*s, *((const BoxCollider *)c), contacts);
        break;
    case Collider::Type::HALF_SPACE:
        SphereHalfSpace(*s, *((const HalfSpace*)c), contacts);
        break;
    case Collider::Type::SPHERE:
        SphereSphere(*s, *((const SphereCollider *)c), contacts);
        break;
    default:
        FR_CRASH("Should not be here");
        break;
    }
}


void CollisionDetector::BoxSomething(const BoxCollider *b, const Collider *c, std::vector<Contact> &contacts)
{
    switch (c->getType())
    {
    case Collider::Type::BOX:
        BoxBox(*b, *((const BoxCollider *)b), contacts);
        break;
    case Collider::Type::HALF_SPACE:
        BoxHalfSpace(*b, *((const HalfSpace *)c), contacts);
        break;
    default:
        FR_CRASH("Should not be here");
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
    contact.friction = 0.5f;
    contacts.push_back(contact);
}


void CollisionDetector::SphereHalfSpace(const SphereCollider &s, const HalfSpace &h, std::vector<Contact> &contacts)
{
    auto S = s.body->getTransformMatrix();
    auto H = h.body->getTransformMatrix();
    fr::Vec3 sPos = S * fr::Vec4{s.position[0], s.position[1], s.position[2], 1};
    fr::Vec3 hNorm = fr::Normal(fr::Vec3(h.body->getOrientation() * fr::Vec4{h.normal[0], h.normal[1], h.normal[2], 1}));
    fr::Real hOffset = fr::Dot(hNorm, h.body->getPosition());

    auto dist = fr::Dot(sPos, hNorm) - hOffset - s.radius;
    if (dist >= 0) return;

    Contact contact;
    contact.point = sPos - hNorm * (dist + s.radius);
    contact.normal = hNorm;
    contact.depth = -dist;
    contact.bodies[0] = s.body;
    contact.bodies[1] = h.body;
    contact.restitution = 0.9f;
    contact.friction = 0.5f;
    contacts.push_back(contact);
}


void CollisionDetector::SphereBox(const SphereCollider &s, const BoxCollider &b, std::vector<Contact> &contacts)
{
    auto S = s.body->getTransformMatrix();
    auto B = b.body->getTransformMatrix() * b.offset.getMat();
    auto sphereCenter = fr::Vec3(S * fr::Vec4{s.position[0], s.position[1], s.position[2], 1});
    auto center = fr::Vec3(fr::Inverse(B) * fr::Vec4{sphereCenter[0], sphereCenter[1], sphereCenter[2], 1});

    if (std::abs(center[0]) - s.radius > b.halfSizes[0] ||
        std::abs(center[1]) - s.radius > b.halfSizes[1] ||
        std::abs(center[2]) - s.radius > b.halfSizes[2])
    {
        return;
    }

    fr::Vec3 closestPt{0,0,0};
    fr::Real dist = 0;

    // clamp each coordinate to the box
    dist = center[0];
    if (dist > b.halfSizes[0]) dist = b.halfSizes[0];
    if (dist < -b.halfSizes[0]) dist = -b.halfSizes[0];
    closestPt[0] = dist;

    dist = center[1];
    if (dist > b.halfSizes[1]) dist = b.halfSizes[1];
    if (dist < -b.halfSizes[1]) dist = -b.halfSizes[1];
    closestPt[1] = dist;

    dist = center[2];
    if (dist > b.halfSizes[2]) dist = b.halfSizes[2];
    if (dist < -b.halfSizes[2]) dist = -b.halfSizes[2];
    closestPt[2] = dist;

    // check for contact
    dist = fr::Len((closestPt - center));
    if (dist > s.radius * s.radius) return;

    // create contact
    fr::Vec3 closestPtWorld = B * closestPt;
    Contact contact;
    contact.point = closestPtWorld;
    contact.normal = fr::Normal(closestPtWorld - sphereCenter);
    contact.depth = s.radius - std::sqrt(dist);
    contact.bodies[0] = s.body;
    contact.bodies[1] = b.body;
    contact.restitution = 0.9f;
    contact.friction = 0.5f;
    contacts.push_back(contact);
}


void CollisionDetector::BoxHalfSpace(const BoxCollider &b, const HalfSpace &h, std::vector<Contact> &contacts)
{
    static fr::Real mults[8][3] = {{1,1,1}, {-1,1,1}, {1,-1,1}, {-1,-1,1}, {1,1,-1}, {-1,1,-1}, {1,-1,-1}, {-1,-1,-1}};
    fr::Mat4 toWorld = b.body->getTransformMatrix() * b.offset.getMat();
    fr::Vec3 hNorm = fr::Normal(fr::Vec3(h.body->getOrientation() * fr::Vec4{h.normal[0], h.normal[1], h.normal[2], 1}));
    fr::Real hOffset = fr::Dot(hNorm, h.body->getPosition());

    for (unsigned int i = 0; i < 8; ++i) {
        fr::Vec3 vertPos {
            mults[i][0] * b.halfSizes[0],
            mults[i][1] * b.halfSizes[1],
            mults[i][2] * b.halfSizes[2]
        };
        vertPos = fr::Vec3(toWorld * fr::Vec4{vertPos[0], vertPos[1], vertPos[2], 1});

        // calculate distance from plane
        fr::Real vertDist = fr::Dot(vertPos, hNorm);

        if (vertDist <= hOffset) {
            Contact contact;
            contact.point = hNorm * (vertDist - hOffset) + vertPos;
            contact.normal = hNorm;
            contact.depth = hOffset - vertDist;
            contact.bodies[0] = b.body;
            contact.bodies[1] = h.body;
            contact.restitution = 0.5f;
            contact.friction = 1.0f;
            contacts.push_back(contact);
        }
    }
}


void CollisionDetector::BoxBox(const BoxCollider &b, const BoxCollider &h, std::vector<Contact> &contacts)
{
    FR_LOG("todo - box box collision");
}
