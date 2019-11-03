#include <glad/glad.h>
#include <glfw3.h>
#include "Freight.hpp"
#include <cmath>
#include "LevelLoader.hpp"
#include "WinSandbox.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    WindowResizeEvent *e = new WindowResizeEvent;
    e->width = width;
    e->height = height;
    fr::EventManager::Instance().post<WindowResizeEvent>(std::shared_ptr<const WindowResizeEvent>(e));
}


int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        FR_DEBUG_LOG("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        FR_DEBUG_LOG("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    auto app = fr::Freight::GetApp();
    app->start();

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