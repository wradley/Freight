#include "GraphicsSystem.hpp"
#include "LoadEvents.hpp"

GraphicsSystem::GraphicsSystem()
{
}


GraphicsSystem::~GraphicsSystem()
{
}


void GraphicsSystem::start(std::shared_ptr<fr::EventManager> em)
{
    em->on<LoadEntityEvent>([](std::shared_ptr<const LoadEntityEvent> e) {
        FR_LOG("Graphics System Loading Entity: " << e->entity);
    });

    em->on<LoadModelComponentEvent>([](std::shared_ptr<const LoadModelComponentEvent> e) {
        FR_LOG("Graphics System Loading Model Component for: " << e->entity);
    });
}


void GraphicsSystem::update(std::shared_ptr<fr::EventManager> em)
{
}


void GraphicsSystem::stop()
{
}
