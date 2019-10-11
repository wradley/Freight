#include "WinSandbox.hpp"
#include "LevelLoader.hpp"
#include "LoadEvents.hpp"


fr::Freight *fr::Freight::GetApp()
{
    return new WinSandbox;
}


WinSandbox::WinSandbox() : 
    fr::Freight(WINSANDBOX_PATH_TO_ASSETS),
    mEventManager(std::make_shared<fr::EventManager>()),
    mLevelLoader(std::make_shared<LevelLoader>(mEventManager)),
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
