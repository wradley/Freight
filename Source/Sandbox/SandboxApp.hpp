#pragma once
#include "Freight/Freight.hpp"

namespace FR8
{
    class SandboxApp : public Freight
    {
    public:

        Error* start();
        Error* update();
        Error* stop();
        
    };
};