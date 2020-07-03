#pragma once
#include "Freight.hpp"
#include "Freight/Gfx.hpp"


class WindowCreationTesting : public fr::Freight
{
public:

    WindowCreationTesting();
    ~WindowCreationTesting();

    virtual void start() override;
    virtual void update() override;
    virtual void stop() override;

private:

    fr::EventManager &mEventManager;

    std::shared_ptr<fr::gfx::ResourceManager> mResourceManager;
    std::unique_ptr<fr::gfx::Env2D> mEnv2D;
    size_t mSpriteNode;
    size_t mCameraNode;
    size_t mSprite;
    size_t mSprite2;
    size_t mCamera;

    std::chrono::high_resolution_clock::time_point mLastTime;
};