#pragma once
#include "Node2DManager.hpp"
#include "Camera2DManager.hpp"
#include "SpriteManager.hpp"
#include "TextManager.hpp"
#include "../Resources/ResourceManager.hpp"

namespace fr::gfx
{
    class Env2D
    {
    public:

        // Dimensions of environment in pixels.
        Env2D(std::shared_ptr<ResourceManager> resourceManager);
        ~Env2D();

        void setFrameBuffer(uint width, uint height);
        void update();
        void capture(size_t camera);

        uint mFbWidth;
        uint mFbHeight;
        std::shared_ptr<ResourceManager> mResourceManager;
        std::shared_ptr<Node2DManager> mNodeManager;
        std::shared_ptr<Camera2DManager> mCameraManager;
        std::shared_ptr<SpriteManager> mSpriteManager;
        std::shared_ptr<TextManager> mTextManager;
    };
}