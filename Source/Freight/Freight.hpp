#pragma once

namespace fr
{
    class Freight
    {
    public:

        virtual ~Freight() {}

        virtual void start() = 0;
        virtual void update() = 0;
        virtual void stop() = 0;
        
        static Freight* GetApp();

    private:
    };
}
