#pragma once

namespace fr8
{
    class RenderGroup2D;
    class RenderGroup3D;

    class Renderer
    {
    public:

        RenderGroup2D* createGroup2D();
        RenderGroup3D* createGroup3D();

    private:
    };
}