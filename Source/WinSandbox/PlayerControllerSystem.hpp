#pragma once
#include "LoadEvents.hpp"
#include "GamePadController.hpp"

class PlayerControllerSystem
{
public:

    PlayerControllerSystem();
    ~PlayerControllerSystem();

    void start();
    void update();
    void stop();

private:

    EntID mPlayerID;
    bool mHasPlayer;
    bool mInitLastXY;
    fr::f64 mXPixelsMoved, mYPixelsMoved;
    fr::Real mPitch, mYaw;
    fr::Transform mPlayerTform;
    GamePadController mController;
    fr::f64 mLastX, mLastY;

    // max pixels mouse moved since last event
    const fr::f64 X_MAX_PIXELS = 100;
    const fr::f64 Y_MAX_PIXELS = 100;

    const fr::Real MOVE_SPEED = 0.3;
    const fr::Real ROT_SPEED_X = 10.0;
    const fr::Real ROT_SPEED_Y = 10.0;
};