#pragma once
#include <Freight/pch.hpp>
#include "Collider.hpp"
#include "Contact.hpp"

class CollisionDetector
{
public:

    static void SphereSphere(const SphereCollider &a, const SphereCollider &b, std::vector<Contact> &contacts);
    static void SpherePlane(const SphereCollider &s, const PlaneCollider &p, std::vector<Contact> &contacts);

};