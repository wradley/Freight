#pragma once
#include "../../Include/Freight/pch.hpp"
#include "../../Math/Matrix.hpp"
#include "glad/glad.h"

namespace fr::gfx
{
    class Node2DManager;
    class FontManager;

    class TextManager
    {
        struct _Text
        {
            size_t parentNode;
            size_t font;
            GLuint vao;
            Vec2 center;
            Real orientation;
            Vec2 size; // width & height
            Real charSpacing;
            i32 layer;
            bool valid;
        };

        std::vector<_Text> mTexts;
        std::vector<size_t> mFreeSlots; // reuse text slots when they are deleted

        // used to calculate global text position and whether or not a parent node has been deleted
        std::shared_ptr<Node2DManager> mNodeManager;
        std::shared_ptr<FontManager> mFontManager;

        GLuint mTextShaderProg;

        // layer to draw the text on
        i32 mMaxLayer;
        i32 mMinLayer;
        bool mLayerModificationSinceLastUpdate; // if we need to recheck min and max layers on the udpate

    public:

        TextManager(std::shared_ptr<Node2DManager> nodeManager, std::shared_ptr<FontManager> fontManager);
        ~TextManager();

        // Using node from node manager.
        size_t createText(size_t parentNode);

        // Delete text by id.
        void deleteText(size_t text);

        // Get the position of the text relative to the parent node from center of text.
        Vec2 getCenter(size_t text) const;

        // Set the position of the text relative to the parent node from center of text.
        void setCenter(size_t text, const Vec2 &center);

        // Get the orientation of the text relative to the parent node.
        Real getOrientation(size_t text) const;

        // Set the orientation of the text relative to the parent node.
        void setOrientation(size_t text, Real orientation);

        // Get text width and height. Will be scaled by any parent scaling.
        Vec2 getSize(size_t text);

        // Set text width and height. Will be scaled by any parent scaling.
        void setSize(size_t text, const Vec2 &size);

        // Get the spacing between the characters. Will be scaled by ancestors.
        Real getCharSpacing(size_t text);

        // Set the spacing between the characters. Will be scaled by ancestors.
        void setCharSpacing(size_t text, Real spacing);

        // Get the text's parent node id.
        size_t getParentNode(size_t text) const;

        // Set the text's parent node id.
        void setParentNode(size_t text, size_t parentNode);

        // Set text's string.
        void setString(size_t text, const fr::String &str);

        // Get the font id the text is using.
        size_t getFont(size_t text);

        // Set the font by id the text is using.
        void setFont(size_t text, size_t font);

        // Get the text's toWorld matrix based on its global position from node ancestors
        Mat3 getToWorld(size_t text);

        // Get layer text is draw on. Smaller number layers are drawn first.
        i32 getLayer(size_t text);

        // Set layer to draw text on. Two texts on the same layer have no guarantee as to drawing order. Default layer is 0.
        void setLayer(size_t text, i32 layer);

        // Run calculations before drawing.
        void update();

        // Get the lowest layer a text is on. Must be called after update.
        i32 getMinLayer();

        // Get the highest layer a text is drawn on. Must be called after update.
        i32 getMaxLayer();

        // Draw the text in world space
        void _draw(Mat3 &projView, i32 minLayer, i32 maxLayer);


        // Text is only a single row. Multiline paragraphs requires multiple text objects.
        // void setCharSizeByWidth(size_t text, Real width);
        // void setCharSizeByHeight(size_t text, Real height);
        // void scaleCharWidth(size_t text, Real scale);
        // void scaleCharHeight(size_t text, Real scale);
        // void setCharPadding(size_t text, Real padding); // left and right
        // void setTextWidth(size_t text, Real size);
        // void setTextWidthUnlimited();
        // void scaleToFitCharacters(size_t text); // scales char size so that all characters fit the max width. Maintains width and height scale previously set.
        // void setLayer(size_t text, i32 layer);
        // size_t setChars(size_t text, fr::String); // no getter. Returns the last character it drew.
        // void allowPartials(size_t text, bool drawPartial); // whether or not to draw the last character if it goes over the max width.
    };
}