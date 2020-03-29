#include <glad/glad.h>
#include <glfw3.h>
#include "Freight.hpp"
#include <cmath>
//#include "LevelLoader.hpp"
#include "MathSandbox.hpp"
#include "LoadEvents.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    WindowResizeEvent *e = new WindowResizeEvent;
    e->width = width;
    e->height = height;
    fr::EventManager::Instance().post<WindowResizeEvent>(std::shared_ptr<const WindowResizeEvent>(e));
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    InputEvent::KeyInput ki;
    ki.openglAction = action;
    ki.openglKey = key;
    auto e = new InputEvent;
    e->keys.push_back(ki);
    fr::EventManager::Instance().post(std::shared_ptr<const InputEvent>(e));
}


static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    InputEvent::MouseMoveEvent mm;
    mm.xpos = xpos;
    mm.ypos = ypos;
    auto e = new InputEvent;
    e->mouseMoves.push_back(mm);
    fr::EventManager::Instance().post(std::shared_ptr<const InputEvent>(e));
}


int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1400, 800, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        FR_DEBUG_LOG("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwSetWindowPos(window, 100, 100);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        FR_DEBUG_LOG("Failed to initialize GLAD");
        return -1;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    auto app = fr::Freight::GetApp();
    app->start();
    framebuffer_size_callback(nullptr, 1400, 800);

    fr::EventManager::Instance().on<ApplicationExitEvent>([&window](std::shared_ptr<const ApplicationExitEvent> e) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    });

    while (!glfwWindowShouldClose(window))
    {
        app->update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app->stop();
    glfwTerminate();
    return 0;
}