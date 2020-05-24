#include "WinSandbox.hpp"
#include "LevelLoader.hpp"
#include "LoadEvents.hpp"


fr::Freight *fr::Freight::GetApp()
{
    return new WinSandbox;
}


WinSandbox::WinSandbox() : 
    fr::Freight(WINSANDBOX_PATH_TO_ASSETS),
    mEventManager(fr::EventManager::Instance()),
    mLevelLoader(),
    mPlayerControllerSystem(std::make_unique<PlayerControllerSystem>()),
    mPhysicsSystem3D(std::make_unique<PhysicsSystem>()),
    mGraphicsSystem(std::make_unique<GraphicsSystem>())
{
}


WinSandbox::~WinSandbox()
{
}


void WinSandbox::start()
{    
    mPlayerControllerSystem->start();
    mPhysicsSystem3D->start();
    mGraphicsSystem->start(mEventManager);
    mLevelLoader->load("Levels/Entry.json");

    mLastTime = std::chrono::high_resolution_clock::now();
}


void WinSandbox::update()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - mLastTime);
    /*while (duration.count() < 100000)
        duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - mLastTime);*/
    fr::Real dt = duration.count() / (fr::Real)1000000;
    mLastTime = now;

    mPlayerControllerSystem->update();
    mPhysicsSystem3D->update(0.0069f);
    //mPhysicsSystem3D->update(dt);
    mGraphicsSystem->update(mEventManager);
}


void WinSandbox::stop()
{
    mGraphicsSystem->stop();
    mPhysicsSystem3D->stop();
    mPlayerControllerSystem->stop();
}
