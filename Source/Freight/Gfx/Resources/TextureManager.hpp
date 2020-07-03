#pragma once
#include "../Include/Freight/pch.hpp"
#include "../FileSystem/Filepath.hpp"
#include "glad/glad.h"

namespace fr::gfx
{
    enum class TextureFormat
    {
        RGB = 0,
        RGBA
    };

    enum class TextureUpscaling
    {
        LINEAR = 0,
        NEAREST
    };

    enum class TextureDownscaling
    {
        // value nearest the specified pixel
        NEAREST = 0,

        // weighted average of four samples
        LINEAR,

        // value nearest the speficied pixel on the closest mipmap
        MIPMAP_NEAREST,

        // weighted average of four samples on the closest mipmap
        MIPMAP_LINEAR,

        // value nearest of the specified pixel between two interpolated mipmaps
        BLENDED_MIPMAP_NEAREST,

        // weighted average of four samples between two interpolated mipmaps
        BLENDED_MIPMAP_LINEAR
    };

    enum TextureWrapping
    {
        CLAMP_TO_EDGE = 0,
        MIRROR_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER,
        MIRROR_REPEAT,
        REPEAT
    };

    struct TextureDesc
    {
        TextureFormat format;
        TextureUpscaling upscaling;
        TextureDownscaling downscaling;
        TextureWrapping verticalWrapping;
        TextureWrapping HorizontalWrapping;
    };

    // texure 0 is reserved for use as a nil texture
    class TextureManager
    {
    public:

        TextureManager();
        ~TextureManager();

        // Load a texture from file. Returns a texture handler on success. Fills the error string on failure.
        size_t loadFromFile(const fr::Filepath &fp, TextureDesc d, fr::String &error);

        // Delete a texture from the texture manager. Make sure the texture is not in use as there will be undefined behavior.
        void deleteTexture(size_t textureId);

        // Get the width of a texture by id.
        u32 getWidth(size_t textureId) const;

        // Get the height of a texture by id.
        u32 getHeight(size_t textureId) const;

        // Remove all textures from manager.
        void clear();

        GLuint _getGlId(size_t texture);

    private:

        struct GlTexture
        {
            bool valid;
            GLuint gid;
            GLsizei width;
            GLsizei height;
        };

        // todo: debug mode where no texture slots a reused and valid checks are done before any call
        std::vector<GlTexture> mTextures;
        std::vector<size_t> mFreeTextureSlots; // reuse texture slots in mTextures before creating new ones
    };

    /*class Texture
    {
    public:

        Texture(std::shared_ptr<TextureManager> manager);
        ~Texture() {
            mManager->deleteTexture(mId);
        }

    private:

        size_t mId;
        std::shared_ptr<TextureManager> mManager;

    };*/
}