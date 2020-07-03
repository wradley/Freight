#include "WindowCreationTesting.hpp"


fr::Freight *fr::Freight::GetApp()
{
    return new WindowCreationTesting;
}


WindowCreationTesting::WindowCreationTesting() : 
    fr::Freight(WINDOWCREATIONTESING_PATH_TO_ASSETS),
    mEventManager(fr::EventManager::Instance()),
    mResourceManager(std::make_shared<fr::gfx::ResourceManager>()),
    mEnv2D(std::make_unique<fr::gfx::Env2D>(mResourceManager))
{
}


WindowCreationTesting::~WindowCreationTesting()
{
}


void WindowCreationTesting::start()
{
    mEnv2D->setFrameBuffer(1400, 800);
    size_t rootNode = mEnv2D->mNodeManager->getRootNode();

    mSpriteNode = mEnv2D->mNodeManager->createNode(rootNode);
    mEnv2D->mNodeManager->setOrientation(mSpriteNode, 0);
    mEnv2D->mNodeManager->setScale(mSpriteNode, {1, 1});
    mEnv2D->mNodeManager->setPosition(mSpriteNode, {0, 0});

    mCameraNode = mEnv2D->mNodeManager->createNode(rootNode);
    mEnv2D->mNodeManager->setOrientation(mCameraNode, 0);
    mEnv2D->mNodeManager->setScale(mCameraNode, {1, 1});
    mEnv2D->mNodeManager->setPosition(mCameraNode, {0.05, 0});

    fr::gfx::TextureDesc desc;
    desc.downscaling = fr::gfx::TextureDownscaling::NEAREST;
    desc.format = fr::gfx::TextureFormat::RGB;
    desc.HorizontalWrapping = fr::gfx::TextureWrapping::REPEAT;
    desc.upscaling = fr::gfx::TextureUpscaling::NEAREST;
    desc.verticalWrapping = fr::gfx::TextureWrapping::REPEAT;

    fr::String err;

    size_t texture = mResourceManager->mTextureManager->loadTextureFile("Textures/RGBYTile.png", desc, err);
    if (err.size()) {
        FR_CRASH(err);
    }

    mSprite = mEnv2D->mSpriteManager->createSprite(mSpriteNode);
    mEnv2D->mSpriteManager->setCenter(mSprite, {0, 0});
    mEnv2D->mSpriteManager->setOrientation(mSprite, 0);
    mEnv2D->mSpriteManager->setSize(mSprite, {0.1, 0.1});
    mEnv2D->mSpriteManager->setTexture(mSprite, texture);
    mEnv2D->mSpriteManager->setLayer(mSprite, -1000);

    mSprite2 = mEnv2D->mSpriteManager->createSprite(mSpriteNode);
    mEnv2D->mSpriteManager->setCenter(mSprite2, {0, 0});
    mEnv2D->mSpriteManager->setOrientation(mSprite2, 0);
    mEnv2D->mSpriteManager->setSize(mSprite2, {0.1, 0.1});
    mEnv2D->mSpriteManager->setTexture(mSprite2, texture);
    mEnv2D->mSpriteManager->setLayer(mSprite2, -100);

    mCamera = mEnv2D->mCameraManager->createCamera(mCameraNode);
    mEnv2D->mCameraManager->setCenter(mCamera, {0, 0});
    mEnv2D->mCameraManager->setOrientation(mCamera, 0);
    mEnv2D->mCameraManager->setSize(mCamera, {1, (fr::Real)800/(fr::Real)1400});
}


void WindowCreationTesting::update()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - mLastTime);
    fr::Real dt = duration.count() / (fr::Real)1000000;
    mLastTime = now;

    static float orientation = 0.0f;
    auto pos = mEnv2D->mNodeManager->getPosition(mSpriteNode);
    pos[0] += 0.0001f;
    pos[1] += 0.0001f;
    //mEnv2D->mNodeManager->setPosition(mSpriteNode, pos);
    mEnv2D->mNodeManager->setOrientation(mCameraNode, orientation);
    mEnv2D->mSpriteManager->setOrientation(mSprite, orientation);
    orientation += 0.005f;
    

    auto size = mEnv2D->mCameraManager->getSize(mCamera);
    size[0]++;
    size[1]++;
    //mEnv2D->mCameraManager->setSize(mCamera, size);

    mEnv2D->update();
    mEnv2D->capture(mCamera);
}


void WindowCreationTesting::stop()
{
}
