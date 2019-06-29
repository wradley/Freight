#pragma once
#include "Freight.hpp"

namespace FR8
{
    class SandboxApp : public Freight
    {
    public:

        void start() override;
        void update() override;
        void stop() override;

    };
}