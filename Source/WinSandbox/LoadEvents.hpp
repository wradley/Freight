#pragma once
#include "Freight.hpp"
#include "Freight/Math.hpp"
#include <json.hpp>

struct AddEntityEvent
{
    fr::EntID entity;
    fr::EntID parent;
    fr::Transform transform;
    std::vector<fr::String> tags;
};


struct RemoveEntityEvent
{
    fr::EntID entity;
};


struct AddComponentEvent
{
    // entity that this component belongs to
    fr::EntID entity;

    // type of component ("collider" or "camera" etc...)
    fr::String type;

    // data describing this component
    nlohmann::json data;
};


struct RemoveComponentEvent
{
    // entity that this component belongs to
    fr::EntID entity;
};


struct AddModelComponentEvent
{
    fr::EntID entity;
    fr::Filepath meshFp;
    fr::Filepath colorFP;
    fr::Transform transform;
};


struct AddCameraComponentEvent
{
    fr::EntID entity;
    fr::Transform transform;
    fr::Real nearPlane;
    fr::Real farPlane;
    fr::Real fieldOfViewY;
};


struct AddColliderComponentEvent
{
    fr::EntID entity;
    enum class ColliderType {
        NIL,
        BOX
    } type;
    fr::Transform transform;
};


struct AddParticleForceGeneratorsEvent
{
    struct Drag
    {

    };

    struct Spring
    {
        fr::Real springConstant;
        fr::Real restLength;
        fr::EntID source;
    };

    enum GeneratorType
    {
        DRAG_GENERATOR,
        SPRING_GENERATOR
    };

    struct Generator
    {
        fr::EntID entity;
        GeneratorType type;
        union {
            Drag drag;
            Spring spring;
        };
    };

    std::vector<Generator> generators;
};


struct AddParticleComponentEvent
{
    fr::EntID entity;
    fr::Real inverseMass;
    AddParticleForceGeneratorsEvent addForceGenerators;
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
        fr::EntID entity;
        fr::Transform transform;
    };

    std::vector<EntityTransform> transforms;
};