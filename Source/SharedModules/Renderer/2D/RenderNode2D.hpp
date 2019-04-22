#pragma once

namespace fr8
{
    class Sprite;

    class RenderNode2D
    {
    public:

        RenderNode2D* createChildNode();
        RenderSprite* createSprite();

    private:
    };
}
