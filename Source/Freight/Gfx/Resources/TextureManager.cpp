#include "TextureManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static const GLuint sGlFormats[] = {
    GL_RGB,
    GL_RGBA
};

static const GLuint sGlUpscalings[] = {
    GL_LINEAR,
    GL_NEAREST
};

static const GLuint sGlDownscalings[] = {
    GL_LINEAR,
    GL_NEAREST,
    GL_NEAREST_MIPMAP_NEAREST,
    GL_NEAREST_MIPMAP_LINEAR,
    GL_LINEAR_MIPMAP_NEAREST,
    GL_LINEAR_MIPMAP_LINEAR
};

static const GLuint sGlWrappings[] = {
    GL_CLAMP_TO_EDGE,
    GL_MIRROR_CLAMP_TO_EDGE,
    GL_CLAMP_TO_BORDER,
    GL_MIRRORED_REPEAT,
    GL_REPEAT
};


namespace fr::gfx
{
    TextureManager::TextureManager()
    {}


    TextureManager::~TextureManager()
    {
        clear();
    }


    size_t TextureManager::loadFromFile(const fr::Filepath &fp, TextureDesc d, fr::String &error)
    {
        // load file ...
        int width, height, channelCount;
        auto imgData = stbi_load(
            fp.absolutePath().c_str(),
            &width,
            &height,
            &channelCount,
            0
        );

        if (!imgData) {
            error = "Could not load file [";
            error.append(fp.absolutePath());
            error.append("]");
            return 0;
        }

        // create texture
        GlTexture texture;
        texture.width = (GLuint) width;
        texture.height = (GLuint) height;
        glGenTextures(1, &texture.gid);
        glBindTexture(GL_TEXTURE_2D, texture.gid);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sGlWrappings[(size_t)d.HorizontalWrapping]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, sGlWrappings[(size_t)d.verticalWrapping]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sGlDownscalings[(size_t)d.downscaling]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sGlUpscalings[(size_t)d.upscaling]);
        GLenum format;
        switch (channelCount)
        {
        case 4:
            format = GL_RGBA;
            break;
        default:
            format = GL_RGB;
            break;
        }
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            sGlFormats[(size_t)d.format],
            texture.width,
            texture.height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            imgData
        );

        if (d.downscaling == TextureDownscaling::BLENDED_MIPMAP_LINEAR  ||
            d.downscaling == TextureDownscaling::BLENDED_MIPMAP_NEAREST ||
            d.downscaling == TextureDownscaling::MIPMAP_LINEAR          ||
            d.downscaling == TextureDownscaling::MIPMAP_NEAREST)
            glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        // see if there are slots available from deleted textures
        size_t slot;
        if (mFreeTextureSlots.size()) {
            slot = mFreeTextureSlots.back();
            mTextures[slot] = texture;
            mFreeTextureSlots.pop_back();
        }
        else {
            slot = mTextures.size();
            mTextures.push_back(texture);
        }
        return slot;
    }


    void TextureManager::deleteTexture(size_t t)
    {
        glDeleteTextures(1, &mTextures[t].gid);
        mTextures[t].valid = false;
        mFreeTextureSlots.push_back(t);
    }


    u32 TextureManager::getWidth(size_t textureId) const
    {
        return (u32) mTextures[textureId].width;
    }


    u32 TextureManager::getHeight(size_t textureId) const
    {
        return (u32) mTextures[textureId].height;
    }


    void TextureManager::clear()
    {
        std::vector<GLuint> textures;
        for (auto &texture : mTextures) {
            if (texture.valid)
                textures.push_back(texture.gid);
        }
        glDeleteTextures((GLsizei)textures.size(), &textures[0]);

        mTextures.clear();
        mFreeTextureSlots.clear();
    }


    GLuint TextureManager::_getGlId(size_t texture)
    {
        return mTextures[texture].gid;
    }
}