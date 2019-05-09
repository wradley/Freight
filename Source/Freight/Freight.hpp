#pragma once
#include "Error.hpp"

namespace FR8
{
    class Freight
    {
    public:
        
        Freight();
        virtual ~Freight();

        virtual Error* start();
        virtual Error* update();
        virtual Error* stop();

    private:

    
    };
}
