#include "FontManager.hpp"
#include "TextureManager.hpp"


namespace fr::gfx
{
    FontManager::FontManager(std::shared_ptr<TextureManager> textureManager) :
        mFonts(),
        mFreeSlots(),
        mTextureManager(textureManager)
    {}


    FontManager::~FontManager()
    {
        clear();
    }


    size_t FontManager::loadFromFile(const fr::Filepath &fp, fr::String &error)
    {
        String texErr;
        TextureDesc desc;
        desc.downscaling = TextureDownscaling::LINEAR;
        desc.format = TextureFormat::RGBA;
        desc.HorizontalWrapping = TextureWrapping::REPEAT;
        desc.upscaling = TextureUpscaling::NEAREST;
        desc.verticalWrapping = TextureWrapping::REPEAT;

        size_t bitmap = mTextureManager->loadFromFile(fp, desc, texErr);
        if (texErr.size()) {
            error = "Trouble reading file. " + texErr;
            return 0;
        }

        _Font font;
        font.bitmap = bitmap;
        font.size = {mTextureManager->getWidth(bitmap), mTextureManager->getHeight(bitmap)};

        static const Real charWidth = 7 * font.size[0] / 128;
        static const Real charHeight = 12 * font.size[1] / 128;
        for (unsigned i = 0; i < 128; ++i) {
            fr::Real x = (i % 16) * charWidth;
            fr::Real y = std::floor(i / 16) * charHeight;
            font.bitmapLocations[i] = fr::Vec4{
                x / font.size[0],
                y / font.size[1],
                (x + charWidth) / font.size[0],
                (y + charHeight) / font.size[1]
            };
        }

        font.valid = true;

        if (mFonts.size()) {
            size_t slot = mFreeSlots.back();
            mFreeSlots.pop_back();
            mFonts[slot] = font;
            return slot;
        }

        mFonts.push_back(font);
        return mFonts.size() - 1;
    }


    void FontManager::deleteFont(size_t font)
    {
        mFonts[font].valid = false;
        mFreeSlots.push_back(font);
    }


    const Vec4 *FontManager::getBitmapLocations(size_t font) const
    {
        return mFonts[font].bitmapLocations;
    }


    void FontManager::clear()
    {
        for (auto &font : mFonts) {
            mTextureManager->deleteTexture(font.bitmap);
        }

        mFonts.clear();
        mFreeSlots.clear();
    }


    GLuint FontManager::_getGlId(size_t font)
    {
        return mTextureManager->_getGlId(mFonts[font].bitmap);
    }
}