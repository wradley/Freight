#include "SpriteManager.hpp"
#include "Node2DManager.hpp"
#include "../Resources/TextureManager.hpp"
#include "../_GL/GLShader.hpp"
#include "../../Math/Conversion.hpp"


namespace fr::gfx
{
    SpriteManager::SpriteManager(std::shared_ptr<Node2DManager> nodeManager, std::shared_ptr<TextureManager> textureManager) :
        mSprites(), 
        mFreeSlots(), 
        mNodeManager(nodeManager), 
        mTextureManager(textureManager), 
        mSpriteShaderProg(0),
        mVAO(0),
        mMaxLayer(0),
        mMinLayer(0),
        mLayerModificationSinceLastUpdate(true)
    {
        // todo: option for shader program creation failure
        mSpriteShaderProg = CreateShaderProgram(
            "Shaders/Shader2DVertex.glsl",
            "Shaders/Shader2DGeometry.glsl",
            "Shaders/Shader2DFragment.glsl"
        );

        glGenVertexArrays(1, &mVAO);
    }


    SpriteManager::~SpriteManager()
    {
        glDeleteVertexArrays(1, &mVAO);
        glDeleteProgram(mSpriteShaderProg);
    }


    size_t SpriteManager::createSprite(size_t parentNode)
    {
        _Sprite sprite;
        sprite.parentNode = parentNode;
        sprite.center = {0, 0};
        sprite.size = {1,1};
        sprite.orientation = (Real)0;
        sprite.texture = 0;
        sprite.layer = 0;
        sprite.valid = true;

        // try to reuse memory
        if (mFreeSlots.size()) {
            size_t slot = mFreeSlots.back();
            mFreeSlots.pop_back();
            mSprites[slot] = sprite;
            return slot;
        }
        mSprites.push_back(sprite);
        return mSprites.size() - 1;
    }


    void SpriteManager::deleteSprite(size_t sprite)
    {
        mSprites[sprite].valid = false;
        mFreeSlots.push_back(sprite);
    }


    Vec2 SpriteManager::getCenter(size_t sprite) const
    {
        return mSprites[sprite].center;
    }


    void SpriteManager::setCenter(size_t sprite, const Vec2 &center)
    {
        mSprites[sprite].center = center;
    }


    Real SpriteManager::getOrientation(size_t sprite) const
    {
        return mSprites[sprite].orientation;
    }


    void SpriteManager::setOrientation(size_t sprite, fr::Real radians)
    {
        mSprites[sprite].orientation = radians;
    }


    Vec2 SpriteManager::getSize(size_t sprite)
    {
        return mSprites[sprite].size;
    }


    void SpriteManager::setSize(size_t sprite, const Vec2 &size)
    {
        mSprites[sprite].size = size;
    }


    size_t SpriteManager::getParentNode(size_t sprite) const
    {
        return mSprites[sprite].parentNode;
    }


    void SpriteManager::setParentNode(size_t sprite, size_t parentNode)
    {
        mSprites[sprite].parentNode = parentNode;
    }


    size_t SpriteManager::getTexture(size_t sprite) const
    {
        return mSprites[sprite].texture;
    }


    void SpriteManager::setTexture(size_t sprite, size_t texture)
    {
        mSprites[sprite].texture = texture;
    }


    Mat3 SpriteManager::getToWorld(size_t s)
    {
        auto local = Transform2D(mSprites[s].center, mSprites[s].orientation, mSprites[s].size);
        auto parent = mNodeManager->getToWorld(mSprites[s].parentNode);
        return parent * local;
    }


    i32 SpriteManager::getLayer(size_t sprite)
    {
        return mSprites[sprite].layer;
    }


    void SpriteManager::setLayer(size_t sprite, i32 layer)
    {
        mSprites[sprite].layer = layer;
        mLayerModificationSinceLastUpdate = true;
    }


    void SpriteManager::update()
    {
        if (!mLayerModificationSinceLastUpdate) 
            return;

        mMinLayer = i32_MAX;
        mMaxLayer = i32_MIN;
        for (auto &sprite : mSprites) {
            if (!sprite.valid) continue;
            if (sprite.layer < mMinLayer) mMinLayer = sprite.layer;
            if (sprite.layer > mMaxLayer) mMaxLayer = sprite.layer;
        }

        mLayerModificationSinceLastUpdate = false;
    }


    i32 SpriteManager::getMinLayer()
    {
        update();
        return mMinLayer;
    }


    i32 SpriteManager::getMaxLayer()
    {
        update();
        return mMaxLayer;
    }


    // todo: faster to load all transformed verticies into buffer and draw? Instead of uniforms...
    void SpriteManager::_draw(Mat3 &projView, i32 minLayer, i32 maxLayer)
    {
        glUseProgram(mSpriteShaderProg);
        glUniformMatrix3fv(glGetUniformLocation(mSpriteShaderProg, "uProjView"), 1, GL_TRUE, &projView[0][0]);

        Real max = (Real)(maxLayer - minLayer);

        for (size_t i = 0; i < mSprites.size(); ++i) {
            if (!mSprites[i].valid)
                continue;

            glBindTexture(GL_TEXTURE_2D, mTextureManager->_getGlId(mSprites[i].texture));
            auto world = getToWorld(i);
            glUniformMatrix3fv(glGetUniformLocation(mSpriteShaderProg, "uWorld"), 1, GL_TRUE, &world[0][0]);
            GLfloat depth = ((Real)(mSprites[i].layer - minLayer) / max) * 0.999 + 0.0005;
            glUniform1f(glGetUniformLocation(mSpriteShaderProg, "uDepth"), depth);
            glBindVertexArray(mVAO);
            glDrawArrays(GL_POINTS, 0, 1);
        }
    }
}