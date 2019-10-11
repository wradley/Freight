#pragma once
#include "String.hpp"

namespace fr
{
    class Freight
    {
    public:

        Freight(const String &filePathToAssets);
        virtual ~Freight();

        virtual void start() = 0;
        virtual void update() = 0;
        virtual void stop() = 0;
        
        static Freight* GetApp();

    private:

        Freight(const Freight &) = delete;
        Freight(Freight &&) = delete;

    };
}
