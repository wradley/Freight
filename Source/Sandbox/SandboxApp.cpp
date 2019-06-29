#include "SandboxApp.hpp"
#include <iostream>

namespace FR8
{
    void SandboxApp::start()
    {
        std::cout << "App Start" << std::endl;
    }

    void SandboxApp::update()
    {
        std::cout << "App Update" << std::endl;
    }

    void SandboxApp::stop()
    {
        std::cout << "App Stop" << std::endl;
    }
}


FR8::Freight* GetApp()
{
    return new FR8::SandboxApp;
}