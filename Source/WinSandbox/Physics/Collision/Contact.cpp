#include "Contact.hpp"
#include "../Rigidbody.hpp"

// todo optimize
void Contact::calculateContactBasisMatrix(fr::Mat3 &toWorld) const
{
    const fr::Vec3 &xAxis = normal;

    fr::Vec3 tmp{1, 0, 0};

    // pointing closer to world x axis than world y axis (use world y)
    if (std::abs(xAxis[0]) > std::abs(xAxis[1])) tmp = {0, 1, 0};

    const fr::Vec3 zAxis = fr::Normal(fr::RHCross(xAxis, tmp));
    const fr::Vec3 yAxis = fr::Normal(fr::RHCross(zAxis, xAxis));

    toWorld = fr::Mat3 {
        { xAxis[0], yAxis[0], zAxis[0] },
        { xAxis[1], yAxis[1], zAxis[1] },
        { xAxis[2], yAxis[2], zAxis[2] }
    };
}


void Contact::calculateContactData(CalculatedContactData &data, fr::Real dt) const
{
    FR_ASSERT(bodies[0] && bodies[1], "Must have at least one body in contact");

    calculateContactBasisMatrix(data.toWorld);

    if (bodies[0]) data.relativeContactPosition[0] = point - bodies[0]->getPosition();
    if (bodies[1]) data.relativeContactPosition[1] = point - bodies[1]->getPosition();

    data.velocity = {0, 0, 0};
    if (bodies[0]) data.velocity += calculateLocalVelocity(0, dt);
    if (bodies[1]) data.velocity -= calculateLocalVelocity(1, dt);

    data.goalDeltaVelocity = calculateGoalVelocity(dt);
}


void ContactResolver::resolveContacts(const std::vector<Contact> &contacts, fr::Real dt)
{
    if (contacts.size() == 0) return;

    auto data = prepareContacts(contacts, dt);
    adjustPositions(contacts, data, dt);
    adjustVelocities(contacts, data, dt);
}


std::vector<CalculatedContactData> ContactResolver::prepareContacts(const std::vector<Contact> &contacts, fr::Real dt)
{
    std::vector<CalculatedContactData> data;
    data.resize(contacts.size());

    for (size_t i = 0; i < contacts.size(); ++i) {
        contacts[i].calculateContactData(data[i], dt);
    }

    return data;
}
