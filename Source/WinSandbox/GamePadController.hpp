#pragma once
#include "Freight.hpp"

struct GamePadController
{
    GamePadController();
    ~GamePadController();

    fr::Real lHorizontal, lVertical; // -1.0 - 1.0
    fr::Real rHorizontal, rVertical; // -1.0 - 1.0
    fr::Real l2, r2;                 //  0.0 - 1.0

    enum class BUTTON_MASK {
        L1      = 1 << 0,
        L3      = 1 << 1,
        R1      = 1 << 2,
        R3      = 1 << 3,
        L_UP    = 1 << 4,
        L_DOWN  = 1 << 5,
        L_LEFT  = 1 << 6,
        L_RIGHT = 1 << 7,
        R_UP    = 1 << 8,
        R_DOWN  = 1 << 9,
        R_LEFT  = 1 << 10,
        R_RIGHT = 1 << 11,
    };

    fr::u32 buttons;
};