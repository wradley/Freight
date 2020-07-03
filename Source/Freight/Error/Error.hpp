#pragma once
#include "../String.hpp"

namespace fr
{
    class Error
    {
    public:

        const String& getErrMsg();

    private:
    };

    class FsError : public Error
    {

    };
}