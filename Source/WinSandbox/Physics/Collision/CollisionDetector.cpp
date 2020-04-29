#include "CollisionDetector.hpp"


void CollisionDetector::SphereSphere(const SphereCollider &a, const SphereCollider &b, std::vector<Contact> &contacts)
{
    auto diff = a.position - b.position;
    auto dist = fr::Len(diff);
    if (dist > (fr::Real)0 || dist >= a.radius + b.radius)
        return;

    Contact contact;
    contact.point = a.position + diff / 2;
    contact.normal = diff / dist;
    contact.depth = a.radius + b.radius - dist;
    contacts.push_back(contact);
}


void CollisionDetector::SpherePlane(const SphereCollider &s, const PlaneCollider &p, std::vector<Contact> &contacts)
{
    auto dist = fr::Dot(s.position, p.normal) - p.offset - s.radius;
    if (dist >= 0) return;

    Contact contact;
    contact.point = s.position - p.normal * (dist + s.radius);
    contact.normal = p.normal;
    contact.depth = -dist;
    contacts.push_back(contact);
}
