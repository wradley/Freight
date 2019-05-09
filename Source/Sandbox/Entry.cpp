#include "SandboxApp.hpp"

int main(int argc, char **argv)
{

    FR8::Freight *app = new FR8::SandboxApp;

    app->start();
    app->update();
    app->stop();

    delete app;
}