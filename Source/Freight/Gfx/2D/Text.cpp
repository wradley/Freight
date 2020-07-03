#include "TextManager.hpp"
#include "../_GL/GLShader.hpp"
#include "../../Math/Conversion.hpp"
#include "Node2DManager.hpp"
#include "../Resources/FontManager.hpp"

namespace fr::gfx
{
    TextManager::TextManager(std::shared_ptr<Node2DManager> nodeManager, std::shared_ptr<FontManager> fontManager) :
        mTexts(), 
        mFreeSlots(), 
        mNodeManager(nodeManager),
        mTextShaderProg(0),
        mFontManager(fontManager),
        mMaxLayer(0),
        mMinLayer(0),
        mLayerModificationSinceLastUpdate(true)
    {
        // todo: option for shader program creation failure
        mTextShaderProg = CreateShaderProgram(
            "Shaders/ShaderTextVertex.glsl",
            "Shaders/ShaderTextGeometry.glsl",
            "Shaders/ShaderTextFragment.glsl"
        );
    }


    TextManager::~TextManager()
    {
        for (auto &text : mTexts) {
            mFontManager->_deleteGlVAO(text.vao);
        }

        glDeleteProgram(mTextShaderProg);
    }


    size_t TextManager::createText(size_t parentNode)
    {
        _Text text;
        text.parentNode = parentNode;
        text.font = 0;
        text.vao = 0;
        text.center = {(Real)0, (Real)0};
        text.orientation = (Real)0;
        text.size = {(Real)0, (Real)0};
        text.charWidth = (Real)0;
        text.layer = 0;
        text.valid = true;

        // try to reuse memory
        if (mFreeSlots.size()) {
            size_t slot = mFreeSlots.back();
            mFreeSlots.pop_back();
            mTexts[slot] = text;
            return slot;
        }
        mTexts.push_back(text);
        return mTexts.size() - 1;
    }


    void TextManager::deleteText(size_t text)
    {
        mTexts[text].valid = false;
        mFreeSlots.push_back(text);
    }


    Vec2 TextManager::getCenter(size_t text) const
    {
        return mTexts[text].center;
    }


    void TextManager::setCenter(size_t text, const Vec2 &center)
    {
        mTexts[text].center = center;
    }


    Real TextManager::getOrientation(size_t text) const
    {
        return mTexts[text].orientation;
    }


    void TextManager::setOrientation(size_t text, Real orientation)
    {
        mTexts[text].orientation = orientation;
    }


    Vec2 TextManager::getSize(size_t text)
    {
        return mTexts[text].size;
    }


    void TextManager::setSize(size_t text, const Vec2 &size)
    {
        mTexts[text].size = size;
    }


    Real TextManager::getCharSpacing(size_t text)
    {
        return mTexts[text].charSpacing;
    }


    void TextManager::setCharSpacing(size_t text, Real spacing)
    {
        mTexts[text].charSpacing = spacing;
    }


    size_t TextManager::getParentNode(size_t text) const
    {
        return mTexts[text].parentNode;
    }


    void TextManager::setParentNode(size_t text, size_t parentNode)
    {
        mTexts[text].parentNode = parentNode;
    }


    void TextManager::setString(size_t text, const fr::String &str)
    {
        if (mTexts[text].vao == 0) {
            mTexts[text].vao = mFontManager->_createGlVAO();
        }

        mFontManager->_updateGlVAO(mTexts[text].font, mTexts[text].vao, str);
    }


    size_t TextManager::getFont(size_t text)
    {
        return mTexts[text].font;
    }


    void TextManager::setFont(size_t text, size_t font)
    {
        mTexts[text].font = font;
    }


    Mat3 TextManager::getToWorld(size_t t)
    {
        auto local = Transform2D(mTexts[t].center, mTexts[t].orientation, mTexts[t].size);
        auto parent = mNodeManager->getToWorld(mTexts[t].parentNode);
        return parent * local;
    }


    i32 TextManager::getLayer(size_t text)
    {
        return mTexts[text].layer;
    }


    void TextManager::setLayer(size_t text, i32 layer)
    {
        mTexts[text].layer = layer;
        mLayerModificationSinceLastUpdate = true;
    }


    void TextManager::update()
    {
        if (!mLayerModificationSinceLastUpdate)
            return;

        mMinLayer = i32_MAX;
        mMaxLayer = i32_MIN;
        for (auto &text : mTexts) {
            if (!text.valid) continue;
            if (text.layer < mMinLayer) mMinLayer = text.layer;
            if (text.layer > mMaxLayer) mMaxLayer = text.layer;
        }

        mLayerModificationSinceLastUpdate = false;
    }


    i32 TextManager::getMinLayer()
    {
        update();
        return mMinLayer;
    }


    i32 TextManager::getMaxLayer()
    {
        update();
        return mMaxLayer;
    }


    void TextManager::_draw(Mat3 &projView, i32 minLayer, i32 maxLayer)
    {
        glUseProgram(mTextShaderProg);
        glUniformMatrix3fv(glGetUniformLocation(mTextShaderProg, "uProjView"), 1, GL_TRUE, &projView[0][0]);

        Real max = (Real)(maxLayer - minLayer);

        for (size_t i = 0; i < mTexts.size(); ++i) {
            if (!mTexts[i].valid)
                continue;

            glBindVertexArray(mTexts[i].vao);
            glBindTexture(GL_TEXTURE_2D, mFontManager->_getGlId(mTexts[i].font));

            auto world = getToWorld(i);
            glUniformMatrix3fv(glGetUniformLocation(mTextShaderProg, "uWorld"), 1, GL_TRUE, &world[0][0]);
            
            GLfloat depth = ((Real)(mTexts[i].layer - minLayer) / max) * 0.999 + 0.0005;
            glUniform1f(glGetUniformLocation(mTextShaderProg, "uDepth"), depth);

            glDrawArrays(GL_POINTS, 0, 1);
        }
    }
}
