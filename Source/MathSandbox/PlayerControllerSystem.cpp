#include "PlayerControllerSystem.hpp"
#include "Freight.hpp"
#include <glfw3.h>

PlayerControllerSystem::PlayerControllerSystem() : 
    mPlayerID(0), mHasPlayer(false), mInitLastXY(false),
    mXPixelsMoved(0.0), mYPixelsMoved(0.0),
    mPitch(0.0), mYaw(0.0)
{
}


PlayerControllerSystem::~PlayerControllerSystem()
{
}


void PlayerControllerSystem::start()
{
    auto &em = fr::EventManager::Instance();

    em.on<AddEntityEvent>([this](std::shared_ptr<const AddEntityEvent> e) {
        for (auto &tag : e->tags) {
            if (tag == "player") {
                mHasPlayer = true;
                mPlayerID = e->entity;
                mPlayerTform = e->transform;
            }
        }
    });

    em.on<InputEvent>([this](std::shared_ptr<const InputEvent> e) {

        for (auto &key : e->keys) {
            // key down
            if (key.openglKey == GLFW_KEY_W && key.openglAction == GLFW_PRESS)
                mController.lVertical += 1.0;
            else if (key.openglKey == GLFW_KEY_S && key.openglAction == GLFW_PRESS)
                mController.lVertical -= 1.0;
            else if (key.openglKey == GLFW_KEY_A && key.openglAction == GLFW_PRESS)
                mController.lHorizontal -= 1.0;
            else if (key.openglKey == GLFW_KEY_D && key.openglAction == GLFW_PRESS)
                mController.lHorizontal += 1.0;

            // key up
            else if (key.openglKey == GLFW_KEY_W && key.openglAction == GLFW_RELEASE)
                mController.lVertical -= 1.0;
            else if (key.openglKey == GLFW_KEY_S && key.openglAction == GLFW_RELEASE)
                mController.lVertical += 1.0;
            else if (key.openglKey == GLFW_KEY_A && key.openglAction == GLFW_RELEASE)
                mController.lHorizontal += 1.0;
            else if (key.openglKey == GLFW_KEY_D && key.openglAction == GLFW_RELEASE)
                mController.lHorizontal -= 1.0;

            // esc -> quit
            else if (key.openglKey == GLFW_KEY_ESCAPE && key.openglAction == GLFW_PRESS) {
                auto ae = new ApplicationExitEvent;
                fr::EventManager::Instance().post(std::shared_ptr<const ApplicationExitEvent>(ae));
            }
        }

        for (auto &move : e->mouseMoves) {
            if (!mInitLastXY) {
                mInitLastXY = true;
                mLastX = move.xpos;
                mLastY = move.ypos;
            }

            mXPixelsMoved += move.xpos - mLastX;
            mYPixelsMoved += move.ypos - mLastY;
            
            mLastX = move.xpos;
            mLastY = move.ypos;
        }        
    });
}


void PlayerControllerSystem::update()
{
    // convert mouse pixels moved to analog stick range
    mController.rHorizontal = mXPixelsMoved / X_MAX_PIXELS;
    mController.rVertical = mYPixelsMoved / Y_MAX_PIXELS;
    mXPixelsMoved = 0;
    mYPixelsMoved = 0;

    // remove errors
    if (mController.lVertical > 1.0) mController.lVertical = 1.0;
    if (mController.lVertical < -1.0) mController.lVertical = -1.0;
    if (mController.lVertical < 0.01 && mController.lVertical > -0.01) mController.lVertical = 0.0;
    if (mController.lHorizontal > 1.0) mController.lHorizontal = 1.0;
    if (mController.lHorizontal < -1.0) mController.lHorizontal = -1.0;
    if (mController.lHorizontal < 0.01 && mController.lHorizontal > -0.01) mController.lHorizontal = 0.0;
    if (mController.rVertical > 1.0) mController.rVertical = 1.0;
    if (mController.rVertical < -1.0) mController.rVertical = -1.0;
    if (mController.rVertical < 0.01 && mController.rVertical > -0.01) mController.rVertical = 0.0;
    if (mController.rHorizontal > 1.0) mController.rHorizontal = 1.0;
    if (mController.rHorizontal < -1.0) mController.rHorizontal = -1.0;
    if (mController.rHorizontal < 0.01 && mController.rHorizontal > -0.01) mController.rHorizontal = 0.0;

    // calculate player movement
    if (!mHasPlayer) return;
    if (mController.lVertical   == 0.0 &&
        mController.lHorizontal == 0.0 &&
        mController.rVertical   == 0.0 &&
        mController.rHorizontal == 0.0   ) return;
    
    fr::Vec3 move{mController.lHorizontal, 0, -mController.lVertical};

    mPitch += fr::ToRad(-mController.rVertical * ROT_SPEED_Y);
    mYaw += fr::ToRad(-mController.rHorizontal * ROT_SPEED_X);

    fr::Quat pitch = fr::AxisAngleToQuat({1,0,0}, mPitch);
    fr::Quat yaw = fr::AxisAngleToQuat({0,1,0}, mYaw);

    mPlayerTform.rotation = yaw * pitch;
    mPlayerTform.position += mPlayerTform.rotation * fr::Normal(move) * MOVE_SPEED;
    TransformEntitiesEvent::EntityTransform entTform;
    entTform.entity = mPlayerID;
    entTform.transform = mPlayerTform;
    auto te = new TransformEntitiesEvent;
    te->transforms.push_back(entTform);
    auto &em = fr::EventManager::Instance();
    em.post<TransformEntitiesEvent>(std::shared_ptr<const TransformEntitiesEvent>(te));
}


void PlayerControllerSystem::stop()
{
}
