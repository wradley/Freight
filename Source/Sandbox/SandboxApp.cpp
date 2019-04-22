#include "SandboxApp.hpp"
#include <iostream>

namespace fr8
{
    Error* SandboxApp::start()
    {
        std::cout << "Sandbox Application Started" << std::endl;
        return nullptr;
    }


    Error* SandboxApp::update()
    {
        std::cout << "Sandbox Application Update" << std::endl;
        return nullptr;
    }


    Error* SandboxApp::stop()
    {
        std::cout << "Sandbox Application Stopped" << std::endl;
        return nullptr;
    }
};