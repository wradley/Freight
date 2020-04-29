#include "Contact.hpp"

void Contact::calculateContactBasis()
{
    // contact normal is newXAxis
    fr::Vec3 newYAxis;
    fr::Vec3 newZAxis;

    // if contact normal is closer to x axis, use world y axis for ortho normal
    if (std::abs(normal[0]) > std::abs(normal[1])) {
        const fr::Real s = (fr::Real)1 / std::sqrt(normal[2] * normal[2] + normal[0] + normal[0]);
        newYAxis[0] = 
    }

    // contact normal is closer to y axis, use world x axis for ortho normal
    else {

    }
}