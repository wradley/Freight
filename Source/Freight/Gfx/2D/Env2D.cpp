#include "Env2D.hpp"
#include "../../Math/Conversion.hpp"

namespace fr::gfx
{
    Env2D::Env2D(std::shared_ptr<ResourceManager> resourceManager) :
        mFbWidth(0), mFbHeight(0),
        mResourceManager(resourceManager),
        mNodeManager(std::make_shared<Node2DManager>()), 
        mCameraManager(std::make_shared<Camera2DManager>(mNodeManager)),
        mSpriteManager(std::make_shared<SpriteManager>(mNodeManager, mResourceManager->mTextureManager))
    {}


    Env2D::~Env2D()
    {}


    void Env2D::setFrameBuffer(uint width, uint height)
    {
        mFbWidth = width;
        mFbHeight = height;
    }


    void Env2D::update()
    {
        mNodeManager->update();
        mSpriteManager->update();
        mTextManager->update();
    }


    void Env2D::capture(size_t camera)
    {
        Mat3 proj = Ortho2D((Real)mFbWidth, (Real)mFbHeight);
        Mat3 view = mCameraManager->getViewMat(camera, mFbWidth, mFbHeight);
        Mat3 projView = proj * view;

        i32 spriteMinLayer = mSpriteManager->getMinLayer();
        i32 spriteMaxLayer = mSpriteManager->getMaxLayer();
        i32 textMinLayer = mTextManager->getMinLayer();
        i32 textMaxLayer = mTextManager->getMaxLayer();
        i32 minLayer = spriteMinLayer < textMinLayer ? spriteMinLayer : textMinLayer;
        i32 maxLayer = spriteMaxLayer > textMaxLayer ? spriteMaxLayer : textMaxLayer;
        
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        mSpriteManager->_draw(projView, minLayer, maxLayer);
        mTextManager->_draw(projView, minLayer, maxLayer);
    }
}
