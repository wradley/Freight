#pragma once
#include "TextureManager.hpp"

namespace fr::gfx
{
    class ResourceManager
    {
    public:

        ResourceManager();
        ~ResourceManager();

        std::shared_ptr<TextureManager> mTextureManager;
        // FontManager mFontManager;
        // MeshManager mMeshManager;

    };
}