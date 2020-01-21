#include "MathSandbox.hpp"
#include "LevelLoader.hpp"
#include "LoadEvents.hpp"


fr::Freight *fr::Freight::GetApp()
{
    return new MathSandbox;
}


MathSandbox::MathSandbox() :
    fr::Freight(WINSANDBOX_PATH_TO_ASSETS),
    mEventManager(fr::EventManager::Instance()),
    mLevelLoader(),
    mPlayerControllerSystem(std::make_unique<PlayerControllerSystem>()),
    mGraphicsSystem(std::make_unique<GraphicsSystem>())
{
}


MathSandbox::~MathSandbox()
{
}


void MathSandbox::start()
{    
    mPlayerControllerSystem->start();
    mGraphicsSystem->start(mEventManager);
    mLevelLoader->load("Levels/MathEntry.json");

    mLastTime = std::chrono::high_resolution_clock::now();
}


void MathSandbox::update()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - mLastTime);
    fr::Real dt = duration.count() / (fr::Real)1000000;
    mLastTime = now;

    mPlayerControllerSystem->update();
    mGraphicsSystem->update(mEventManager);
}


void MathSandbox::stop()
{
    mGraphicsSystem->stop();
    mPlayerControllerSystem->stop();
}
