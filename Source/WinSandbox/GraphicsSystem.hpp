#pragma once
#include "Freight.hpp"

class GraphicsSystem
{
public:

    GraphicsSystem();
    ~GraphicsSystem();

    void start(std::shared_ptr<fr::EventManager> em);
    void update(std::shared_ptr<fr::EventManager> em);
    void stop();

private:
};