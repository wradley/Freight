#pragma once
#include "Error.hpp"

namespace fr8
{
    class Application
    {
    public:
        
        virtual ~Application() {}

        virtual Error* start() = 0;
        virtual Error* update() = 0;
        virtual Error* stop() = 0;

    };
}
