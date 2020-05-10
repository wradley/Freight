#pragma once
#include <Freight.hpp>
#include <Freight/Math.hpp>
class Rigidbody;

struct CalculatedContactData
{
    // from contact space to world space
    fr::Mat3 toWorld;

    // closing velocity at point of contact
    fr::Vec3 velocity;

    // required change in velocity for contact to be resolved
    fr::Real goalDeltaVelocity;

    // world-space position of contact point relative to each body
    fr::Vec3 relativeContactPosition[2];
};

struct Contact
{
    // bodies involved in contact. One can be null for immovable objects
    std::shared_ptr<const Rigidbody> bodies[2];

    // point of contact in world space
    fr::Vec3 point;

    // direction of contact in world space
    fr::Vec3 normal;

    // depth of contact from contact point
    fr::Real depth;

    // calculates the toWorld matrix
    void calculateContactBasisMatrix(fr::Mat3 &m) const;

    fr::Vec3 calculateLocalVelocity(unsigned int bodyIndex, const CalculatedContactData &data, fr::Real dt) const;

    // calculate contact data
    void calculateContactData(CalculatedContactData &data, fr::Real dt) const;
};


class ContactResolver
{
public:

    void resolveContacts(const std::vector<Contact> &contacts, fr::Real dt);

private:

    std::vector<CalculatedContactData> prepareContacts(const std::vector<Contact> &contacts, fr::Real dt);
    void adjustPositions(const std::vector<Contact> &contacts, const std::vector<CalculatedContactData> &data, fr::Real dt);
    void adjustVelocities(const std::vector<Contact> &contacts, const std::vector<CalculatedContactData> &data, fr::Real dt);

};