#pragma once
#include <string>
#include <sstream>
#include <mutex>
#include "../Defines.hpp"

#define FR8_DBG_LOG(msg) {\
    std::wstringstream stream;\
    stream << msg;\
    FR8::Logger::Log(L"Info", stream.str(), __FILEW__, __LINE__);\
}

#define FR8_DBG_WARN(msg) {\
    std::wstringstream stream;\
    stream << msg;\
    FR8::Logger::Log(L"Warning", stream.str(), __FILEW__, __LINE__);\
}

#define FR8_DBG_ERR(msg) {\
    std::wstringstream stream;\
    stream << msg;\
    FR8::Logger::Log(L"Error", stream.str(), __FILEW__, __LINE__);\
}

#define FR8_DBG_ASSERT(condition, msg) if (!condition) {\
    std::wstringstream stream;\
    stream << msg;\
    FR8::Logger::Log(L"Assert", stream.str(), __FILEW__, __LINE__);\
}


namespace FR8
{
    class Logger
    {
    public:

        static void Log(
            const std::wstring &prefix,
            const std::wstring &message,
            const std::wstring &filepath,
            size_t lineNumber
        );

        static void Flush();

    private:

        static void LocklessFlush();

    private:

        static const size_t BUFFER_SIZE = 100000;
        static std::mutex sMutex;
        static wchar_t sBuffer[BUFFER_SIZE];
        static size_t sIndex;

    };
}
