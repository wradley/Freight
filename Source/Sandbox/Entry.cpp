#include "SandboxApp.hpp"

int main(int argc, char **argv)
{
    fr8::Application *app = new fr8::SandboxApp;

    app->start();
    app->update();
    app->stop();

    delete app;
}