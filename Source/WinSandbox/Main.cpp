#include <glad/glad.h>
#include <glfw3.h>
#include "Freight.hpp"
#include <cmath>
#include <json.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void testfn();

int main(int argc, char **argv)
{
    testfn();

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


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


// ----------------------------------------------------------------

class TestEvent
{
    fr::String mName;
public:
    TestEvent(const fr::String &name) : mName(name) {}
    ~TestEvent() {}
    fr::String getName() const { return mName; }
};


struct TestB
{
    TestB(int d) : data(d) {}
    int data;
};


void testfn()
{
    fr::EventManager em;
    em.on<TestEvent>([](std::shared_ptr<const TestEvent> evnt) {
        FR_DEBUG_LOG("TestEvent Handler: " << evnt->getName());
    });

    em.on<TestB>([](std::shared_ptr<const TestB> evnt) {
        FR_DEBUG_WARN("TestB Handler 1: " << evnt->data);
    });

    em.on<TestB>([](std::shared_ptr<const TestB> evnt) {
        FR_DEBUG_ERR("TestB Handler 2: " << evnt->data);
    });

    em.post<TestEvent>(std::make_shared<const TestEvent>("test a"));
    em.post<TestEvent>(std::make_shared<const TestEvent>("test b"));

    em.post(std::make_shared<const TestB>(1));
    em.post(std::make_shared<const TestB>(2));
    em.post(std::make_shared<const TestB>(3));
}