#include "Camera2D.hpp"

namespace fr::gfx
{



    /*Mat3 Camera2DManager::getViewMat(size_t camera, uint fbWidth, uint fbHeight)
    {
        Vec2 size{
            mCameras[camera].size[0] / (Real)fbWidth,
            mCameras[camera].size[1] / (Real)fbHeight
        };
        auto local = Transform2D(mCameras[camera].center, mCameras[camera].orientation, size);
        auto world = mNodeManager->getToWorld(mCameras[camera].parentNode) * local;
        return Inverse(world);
    }*/
}