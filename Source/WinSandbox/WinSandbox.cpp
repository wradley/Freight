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
    mGraphicsSystem(std::make_unique<GraphicsSystem>())
{
}


WinSandbox::~WinSandbox()
{
}


void WinSandbox::start()
{    
    mGraphicsSystem->start(mEventManager);
    mLevelLoader->load("Levels/Entry.json");
}


void WinSandbox::update()
{
    mGraphicsSystem->update(mEventManager);
}


void WinSandbox::stop()
{
    mGraphicsSystem->stop();
}
