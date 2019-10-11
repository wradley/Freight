#pragma once
#include "Freight.hpp"
#include "Math.hpp"

using EntID = fr::u64;


struct LoadEntityEvent
{
    EntID entity;
    fr::Transform transform;
};


struct LoadModelComponentEvent
{
    EntID entity;
    fr::Filepath meshFp;
    fr::Filepath colorFP;
    fr::Transform transform;
};


struct LoadColliderComponentEvent
{
    EntID entity;
};