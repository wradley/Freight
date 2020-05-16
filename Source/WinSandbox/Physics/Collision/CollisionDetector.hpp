#pragma once
#include <Freight/pch.hpp>
#include "Collider.hpp"
#include "Contact.hpp"

class CollisionDetector
{
public:
    static void Detect(const Collider *a, const Collider *b, std::vector<Contact> &contacts);
    static void SphereSphere(const SphereCollider &a, const SphereCollider &b, std::vector<Contact> &contacts);
    static void SphereHalfSpace(const SphereCollider &s, const HalfSpace &p, std::vector<Contact> &contacts);
};