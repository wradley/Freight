#pragma once
#include "Freight.hpp"
#include "PlayerControllerSystem.hpp"
#include "GraphicsSystem.hpp"

class LevelLoader;

class WinSandbox : public fr::Freight
{
public:

    WinSandbox();
    ~WinSandbox();

    virtual void start() override;
    virtual void update() override;
    virtual void stop() override;

private:

    fr::EventManager &mEventManager;
    std::shared_ptr<LevelLoader> mLevelLoader;

    std::unique_ptr<PlayerControllerSystem> mPlayerControllerSystem;
    std::unique_ptr<GraphicsSystem> mGraphicsSystem;
};