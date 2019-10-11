#include "Freight.hpp"
#include "Filepath.hpp"

namespace fr
{
    Freight::Freight(const String &filePathToAssets)
    {
        Filepath::SetPathToBaseDir(filePathToAssets);
    }


    Freight::~Freight()
    {
    }
}

//int main() {
//    fr::Freight *app = GetApp();
//    app->start();
//    app->update();
//    app->stop();
//    delete app;
//    return 0;
//}
