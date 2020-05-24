#pragma once
#include <Freight/pch.hpp>
#include "Collider.hpp"
#include "Contact.hpp"

class CollisionDetector
{
public:
    static void Detect(const Collider *a, const Collider *b, std::vector<Contact> &contacts);
    static void SphereSomething(const SphereCollider *s, const Collider *c, std::vector<Contact> &contacts);
    static void BoxSomething(const BoxCollider *b, const Collider *c, std::vector<Contact> &contacts);

    static void SphereSphere(const SphereCollider &a, const SphereCollider &b, std::vector<Contact> &contacts);
    static void SphereHalfSpace(const SphereCollider &s, const HalfSpace &p, std::vector<Contact> &contacts);
    static void SphereBox(const SphereCollider &s, const BoxCollider &b, std::vector<Contact> &contacts);

    static void BoxHalfSpace(const BoxCollider &b, const HalfSpace &h, std::vector<Contact> &contacts);
    static void BoxBox(const BoxCollider &b, const BoxCollider &h, std::vector<Contact> &contacts);
};