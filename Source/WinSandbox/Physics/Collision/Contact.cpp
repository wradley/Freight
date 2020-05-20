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


void Contact::calculateContactData(fr::Real dt, fr::Real velocityEpsilon)
{
    if (!bodies[0]) {
        auto tmp = bodies[1];
        bodies[1] = bodies[0];
        bodies[0] = tmp;
    }
    FR_ASSERT(bodies[0], "Must have at least one body in contact");

    calculateContactBasisMatrix(toWorld);

    relativeContactPosition[0] = point - bodies[0]->getPosition();
    if (bodies[1]) relativeContactPosition[1] = point - bodies[1]->getPosition();

    velocity = calculateLocalVelocity(0, dt);
    if (bodies[1]) velocity -= calculateLocalVelocity(1, dt);

    calculateGoalDeltaVelocity(dt, velocityEpsilon);
}


fr::Vec3 Contact::calculateFrictionImpulse(fr::Mat3 inverseInertiaTensor[2]) const
{
    fr::Real inverseMass = bodies[0]->getInverseMass();
    fr::Mat3 impulseToTorque = fr::SkewSymmetric(relativeContactPosition[0]);

    // matrix to convert contact impulse to dVel in world space
    fr::Mat3 dVelWorld = impulseToTorque * inverseInertiaTensor[0] * impulseToTorque * -1;

    if (bodies[1]) {
        inverseMass += bodies[1]->getInverseMass();
        impulseToTorque = fr::SkewSymmetric(relativeContactPosition[1]);
        dVelWorld += impulseToTorque * inverseInertiaTensor[1] * impulseToTorque * -1;
    }


    // todo remove -- for debugging
    impulseToTorque = fr::SkewSymmetric(relativeContactPosition[0]);

    // change of basis to contact coordinates
    fr::Mat3 dVel = fr::Transpose(toWorld) * dVelWorld * toWorld;

    // add linear change in velocity
    dVel[0][0] += inverseMass;
    dVel[1][1] += inverseMass;
    dVel[2][2] += inverseMass;

    // impulse needed per unit velocity
    fr::Mat3 impulseMatrix = fr::Inverse(dVel);

    // target velocities to kill
    fr::Vec3 velKill{goalDeltaVelocity, -velocity[1], -velocity[2]};

    // find the impulse to kill target velocities
    fr::Vec3 impulseContact = impulseMatrix * velKill;

    // Check for exceeding friction
    fr::Real planarImpulse = std::sqrt(impulseContact[1] * impulseContact[1] + impulseContact[2] * impulseContact[2]);
    if (planarImpulse > impulseContact[0] * friction) {
        // dynamic friction
        impulseContact[1] /= planarImpulse;
        impulseContact[2] /= planarImpulse;
        impulseContact[0] = dVel[0][0] + dVel[0][1] * friction * impulseContact[1] + dVel[0][2] * friction * impulseContact[2];

        impulseContact[0] = goalDeltaVelocity / impulseContact[0];
        impulseContact[1] *= friction * impulseContact[0];
        impulseContact[2] *= friction * impulseContact[0];
    }

    return impulseContact;
}


fr::Vec3 Contact::calculateFrictionlessImpulse(fr::Mat3 inverseInertiaTensor[2]) const
{
    // change in velocity in world space for unit impulse in direction of contact normal
    fr::Vec3 dVelWorld = fr::RHCross(relativeContactPosition[0], normal);
    dVelWorld = inverseInertiaTensor[0] * dVelWorld;
    dVelWorld = fr::RHCross(dVelWorld, relativeContactPosition[0]);

    // to contact coordinates
    fr::Real dVel = fr::Dot(dVelWorld, normal);

    // add linear component of velocity change
    dVel += bodies[0]->getInverseMass();

    if (bodies[1]) {
        // change in velocity in world space for unit impulse in direction of contact normal
        fr::Vec3 dVelWorld = fr::RHCross(relativeContactPosition[1], normal);
        dVelWorld = inverseInertiaTensor[1] * dVelWorld;
        dVelWorld = fr::RHCross(dVelWorld, relativeContactPosition[1]);

        // to contact coordinates
        dVel += fr::Dot(dVelWorld, normal);

        // add linear component of velocity change
        dVel += bodies[1]->getInverseMass();
    }

    // calculate required size of impulse
    return fr::Vec3{ goalDeltaVelocity / dVel, 0, 0 };
}


fr::Vec3 Contact::calculateLocalVelocity(unsigned int bodyIndex, fr::Real dt) const
{
    const Rigidbody *body = bodies[bodyIndex].get();

    // velocity of contact point
    fr::Vec3 velocity = fr::RHCross(body->getRotation(), relativeContactPosition[bodyIndex]) + body->getVelocity();

    // velocity to contact coordinates
    fr::Vec3 contactVelocity = fr::Transpose(toWorld) * velocity;

    // calculate amt of velocity due to forces without reactions
    fr::Vec3 accVelocity = body->getLastFrameAcceleration() * dt;
    accVelocity = fr::Transpose(toWorld) * accVelocity;

    // only interested in planar acceleration
    accVelocity[0] = 0;

    // add planar velocities
    return contactVelocity + accVelocity;
}


void Contact::calculateGoalDeltaVelocity(fr::Real dt, fr::Real velocityEpsilon)
{
    const static fr::Real minVel = 0.1;

    fr::Vec3 scaledContact = normal * dt;
    fr::Real velFromAcc = fr::Dot(bodies[0]->getLastFrameAcceleration(), scaledContact);
    if (bodies[1]) {        
        velFromAcc -= fr::Dot(bodies[1]->getLastFrameAcceleration(), scaledContact);
    }
    
    fr::Real thisResitution = restitution;
    if (std::abs(velocity[0]) < minVel)
        thisResitution = 0.0f;

    goalDeltaVelocity = -velocity[0] - thisResitution * (velocity[0] - velFromAcc);
}


void Contact::applyPositionChange(fr::Vec3 dLinear[2], fr::Vec3 dAngular[2], fr::Real penetration) const
{
    fr::Real totalInertia = (fr::Real) 0;
    fr::Real angularInertia[2];
    fr::Real linearInertia[2];

    // calculate intertia of each object in direction of contact normal due to angular inertia
    for (unsigned int i = 0; i < 2; ++i) {
        fr::Mat3 inverseInertiaTensor = bodies[i]->getInverseInertiaTensorToWorld();

        // change in velocity in world space for unit impulse in direction of contact normal
        fr::Vec3 angularInertiaWorld = fr::RHCross(relativeContactPosition[i], normal);
        angularInertiaWorld = inverseInertiaTensor * angularInertiaWorld;
        angularInertiaWorld = fr::RHCross(angularInertiaWorld, relativeContactPosition[i]);
        angularInertia[i] = fr::Dot(angularInertiaWorld, normal);

        // linear is just inverse mass
        linearInertia[i] = bodies[i]->getInverseMass();

        // end loop here so we have total inertia before continuing
        totalInertia += linearInertia[i] + angularInertia[i];
    }

    const fr::Real angularLimit = (fr::Real) 0.2;
    fr::Real angularMove[2];
    fr::Real linearMove[2];

    // calculate and apply changes
    for (unsigned int i = 0; i < 2; ++i) {
        fr::Real sign = (i == 0) ? 1 : -1;
        angularMove[i] = sign * penetration * (angularInertia[i] / totalInertia);
        linearMove[i] = sign * penetration * (linearInertia[i] / totalInertia);

        // limit the angular move
        fr::Vec3 projection = relativeContactPosition[i] + normal * -fr::Dot(relativeContactPosition[i], normal);
        fr::Real maxMagnitude = angularLimit * fr::Len(projection);

        if (angularMove[i] < -maxMagnitude) {
            fr::Real totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = -maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }
        else if (angularMove[i] > maxMagnitude) {
            fr::Real totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }

        // calculate desired rotation
        if (fr::Eql(angularMove[i], 0)) {
            dAngular[i] = {0, 0, 0};
        }
        else {
            // direction we want to rotate in
            fr::Vec3 targetAngularDirection = fr::RHCross(relativeContactPosition[i], normal);

            auto inverseInertiaTensor = bodies[i]->getInverseInertiaTensorToWorld();

            dAngular[i] = (inverseInertiaTensor * targetAngularDirection) * (angularMove[i] / angularInertia[i]);
        }

        // calculate desired linear
        dLinear[i] = normal * linearMove[i];

        // apply linear movement
        auto pos = bodies[i]->getPosition() + (normal * linearMove[i]);
        bodies[i]->setPosition(pos);

        // apply change in rotation
        auto orientation = bodies[i]->getOrientation() + dAngular[i];
        bodies[i]->setOrientation(orientation);

        // calculate so changes are reflected in body's data
        bodies[i]->calculateCachedValues();
    }
}


void Contact::applyVelocityChange(fr::Vec3 dVel[2], fr::Vec3 dRot[2])
{
    // inverse tensor to contact space
    fr::Mat3 inverseInertiaTensor[2];
    inverseInertiaTensor[0] = bodies[0]->getInverseInertiaTensorToWorld();
    if (bodies[1])
        inverseInertiaTensor[1] = bodies[1]->getInverseInertiaTensorToWorld();

    fr::Vec3 impulseContact;
    if (fr::Eql(friction, 0)) {
        impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
    }
    else {
        impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
    }

    // to world
    fr::Vec3 impulse = toWorld * impulseContact;

    // split to linear and rotational
    fr::Vec3 impulseTorque = fr::RHCross(relativeContactPosition[0], impulse);
    dRot[0] = inverseInertiaTensor[0] * impulseTorque;
    dVel[0] = impulse * bodies[0]->getInverseMass();

    // apply
    bodies[0]->setVelocity(bodies[0]->getVelocity() + dVel[0]);
    bodies[0]->setRotation(bodies[0]->getRotation() + dRot[0]);

    if (bodies[1]) {
        // split to linear and rotational
        fr::Vec3 impulseTorque = fr::RHCross(impulse, relativeContactPosition[1]);
        dRot[1] = inverseInertiaTensor[1] * impulseTorque;
        dVel[1] = impulse * -bodies[1]->getInverseMass();

        // apply
        bodies[1]->setVelocity(bodies[1]->getVelocity() + dVel[1]);
        bodies[1]->setRotation(bodies[1]->getRotation() + dRot[1]);
    }
}


ContactResolver::ContactResolver(
    fr::uint positionResolutionIterations, 
    fr::uint velocityResolutionIterations, 
    fr::Real penetrationEpsilon,
    fr::Real velocityEpsilon
) :
    mPositionIterations(positionResolutionIterations),
    mVelocityIterations(velocityResolutionIterations),
    mPenetrationEpsilon(penetrationEpsilon),
    mVelocityEpsilon(velocityEpsilon)
{}


void ContactResolver::setIterations(size_t i)
{
    mPositionIterations = i;
    mVelocityIterations = i;
}


void ContactResolver::resolveContacts(std::vector<Contact> &contacts, fr::Real dt)
{
    if (contacts.size() == 0) return;
    prepareContacts(contacts, dt);
    adjustPositions(contacts, dt);
    adjustVelocities(contacts, dt);
}


void ContactResolver::prepareContacts(std::vector<Contact> &contacts, fr::Real dt)
{
    for (size_t i = 0; i < contacts.size(); ++i) {
        contacts[i].calculateContactData(dt, mVelocityEpsilon);
    }
}


void ContactResolver::adjustPositions(std::vector<Contact> &contacts, fr::Real dt)
{
    auto itersLeft = mPositionIterations;
    while (itersLeft--) {

        size_t worstContactIndex = contacts.size();
        fr::Real largestDepth = mPenetrationEpsilon;

        // find contact with greatest penetration
        for (size_t contact = 0; contact < contacts.size(); ++contact) {
            if (contacts[contact].depth > largestDepth) {
                worstContactIndex = contact;
                largestDepth = contacts[contact].depth;
            }
        }

        if (worstContactIndex == contacts.size()) break; // done early
        auto &worstContact = contacts[worstContactIndex];

        fr::Vec3 dLinear[2], dAngular[2];
        worstContact.applyPositionChange(dLinear, dAngular, largestDepth);

        // check each contact for updates do to this position change
        for (size_t contactIndex = 0; contactIndex < contacts.size(); ++contactIndex) {
            auto &contact = contacts[contactIndex];

            // check each contact's bodies...
            for (unsigned int contactBody = 0; contactBody < 2; ++contactBody) {
                if (!contact.bodies[contactBody]) continue;

                // ...against this modified contact's bodies
                for (unsigned int worstContactBody = 0; worstContactBody < 2; ++worstContactBody) {

                    // if the other contact contains the body involved in this worst contact, we must update the other contact
                    if (contact.bodies[contactBody] == worstContact.bodies[worstContactBody]) {
                        fr::Vec3 dPos = dLinear[worstContactBody] + fr::RHCross(dAngular[worstContactBody], contact.relativeContactPosition[contactBody]);
                        contact.depth += fr::Dot(dPos, contact.normal * (contactBody ? 1 : -1));
                    }
                }
            }
        }
    }
}


void ContactResolver::adjustVelocities(std::vector<Contact> &contacts, fr::Real dt)
{
    auto itersLeft = mPositionIterations;
    while (itersLeft--) {

        size_t worstContactIndex = contacts.size();
        fr::Real largestVelocity = mVelocityEpsilon;

        // find contact with greatest closing velocity
        for (size_t contact = 0; contact < contacts.size(); ++contact) {
            if (contacts[contact].goalDeltaVelocity > largestVelocity) {
                worstContactIndex = contact;
                largestVelocity = contacts[contact].goalDeltaVelocity;
            }
        }

        if (worstContactIndex == contacts.size()) break; // done early
        auto &worstContact = contacts[worstContactIndex];

        fr::Vec3 dVelocity[2], dRotation[2];
        worstContact.applyVelocityChange(dVelocity, dRotation);

        // change in velocity could have changed other closing velocities
        for (size_t contactIndex = 0; contactIndex < contacts.size(); ++contactIndex) {
            auto &contact = contacts[contactIndex];

            // check each contact's bodies...
            for (unsigned int contactBody = 0; contactBody < 2; ++contactBody) {
                if (!contact.bodies[contactBody]) continue;

                // ... against this modified contact's bodies
                for (unsigned int worstContactBody = 0; worstContactBody < 2; ++worstContactBody) {

                    // if the other contact contains the body involved in this worst contact, we must update the other contact
                    if (contact.bodies[contactBody] == worstContact.bodies[worstContactBody]) {
                        fr::Vec3 dVel = dVelocity[worstContactBody] + fr::RHCross(dRotation[worstContactBody], contact.relativeContactPosition[contactBody]);
                        
                        // negative change if first body in contact
                        contact.velocity += fr::Transpose(contact.toWorld) * dVel * (contactBody ?-1 : 1);
                        contact.calculateGoalDeltaVelocity(dt, mVelocityEpsilon);
                    }
                }
            }
        }
    }
}
