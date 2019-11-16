#pragma once
#include "Freight.hpp"
#include "Freight/Math.hpp"

using EntID = fr::u64;


struct LoadEntityEvent
{
    EntID entity;
    EntID parent;
    fr::Transform transform;
    std::vector<fr::String> tags;
};


struct LoadModelComponentEvent
{
    EntID entity;
    fr::Filepath meshFp;
    fr::Filepath colorFP;
    fr::Transform transform;
};


struct LoadCameraComponentEvent
{
    EntID entity;
    fr::Transform transform;
    fr::Real nearPlane;
    fr::Real farPlane;
    fr::Real fieldOfViewY;
};


struct LoadColliderComponentEvent
{
    EntID entity;
    enum class ColliderType {
        NIL,
        BOX
    } type;
    fr::Transform transform;
};


struct WindowResizeEvent
{
    int width;
    int height;
};


struct ApplicationExitEvent
{

};


struct InputEvent
{
    struct KeyInput
    {
        int openglKey;
        int openglAction;
    };

    struct MouseMoveEvent
    {
        fr::Real xpos;
        fr::Real ypos;
    };

    std::vector<KeyInput> keys;
    std::vector<MouseMoveEvent> mouseMoves;
};


struct TransformEntitiesEvent
{
    struct EntityTransform
    {
        EntID entity;
        fr::Transform transform;
    };

    std::vector<EntityTransform> transforms;
};