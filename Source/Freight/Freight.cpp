#include "Freight.hpp"
#include <iostream>

namespace FR8
{
}

extern FR8::Freight* GetApp();

int main() {
    FR8::Freight *app = GetApp();
    app->start();
    app->update();
    app->stop();
    delete app;
    return 0;
}