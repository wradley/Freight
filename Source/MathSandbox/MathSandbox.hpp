#pragma once
#include "Freight.hpp"
#include "PlayerControllerSystem.hpp"
#include "GraphicsSystem.hpp"
#include <chrono>

class LevelLoader;

class MathSandbox : public fr::Freight
{
public:

    MathSandbox();
    ~MathSandbox();

    virtual void start() override;
    virtual void update() override;
    virtual void stop() override;

private:

    fr::EventManager &mEventManager;
    std::shared_ptr<LevelLoader> mLevelLoader;

    std::unique_ptr<PlayerControllerSystem> mPlayerControllerSystem;
    std::unique_ptr<GraphicsSystem> mGraphicsSystem;

    std::chrono::high_resolution_clock::time_point mLastTime;
};