#pragma once
#include "Application/Application.hpp"

namespace fr8
{
    class SandboxApp : public Application
    {
    public:

        Error* start();
        Error* update();
        Error* stop();
        
    };
};