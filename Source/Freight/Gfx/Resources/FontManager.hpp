#pragma once
#include "../Include/Freight/pch.hpp"
#include "../FileSystem/Filepath.hpp"
#include "../../Math/Vector.hpp"
#include "glad/glad.h"

namespace fr::gfx
{
    class TextureManager;

    class FontManager
    {
        struct _Font
        {
            size_t bitmap;
            UVec2 size; // width & height
            Vec4 bitmapLocations[128];
            u8 asciiMap[128];
            bool valid;
        };

        std::vector<_Font> mFonts;
        std::vector<size_t> mFreeSlots; // reuse deleted font slots in mFonts

        std::shared_ptr<TextureManager> mTextureManager;

    public:

        FontManager(std::shared_ptr<TextureManager> textureManager);
        ~FontManager();

        // Load a font from a font file.
        size_t loadFromFile(const fr::Filepath &fp, fr::String &error);

        // Delete a font by id.
        void deleteFont(size_t font);

        // Get the character locations on the bitmap for a font.
        const Vec4* getBitmapLocations(size_t font) const;

        // Clear all fonts from the manager.
        void clear();

        // Get openGL bitmap texture id.
        GLuint _getGlId(size_t font);

        // Create a new vao with proper attributes for text. Remember to delete the vao when done.
        GLuint _createGlVAO();

        GLuint _deleteGlVAO(GLuint vao);
        
        // Fill vbo with character data given vao.
        void _updateGlVAO(size_t font, GLuint vao, const fr::String &str);
    };
}