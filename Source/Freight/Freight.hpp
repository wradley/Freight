#pragma once

namespace FR8
{
    class Freight
    {
    public:

        virtual ~Freight() {}

        virtual void start() = 0;
        virtual void update() = 0;
        virtual void stop() = 0;

    private:
    };
}