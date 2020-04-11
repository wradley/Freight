#include "Log.hpp"
#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

namespace fr
{
    std::mutex Logger::sMutex;

    // TODO: compile time?
    fr::String TrimPath(const fr::String &filepath, const fr::String delimiter)
    {
        auto index = filepath.find(delimiter);
        if (index != fr::String::npos) {
            index += delimiter.size();
            return filepath.substr(index, filepath.size() - index + 1);
        }
        return filepath;
    }


    void CopyToBuffer(wchar_t *dst, const wchar_t *src, size_t length)
    {
        for (size_t i = 0; i < length; ++i) {
            dst[i] = src[i];
        }
    }


    void Logger::Log(
        Type type,
        const fr::String &message,
        const fr::String &filepath,
        size_t lineNumber
    ){
        // "[<prefix>] "  "<filepath>"  "[<lineNumber>]: "  "<message>" "\n"

        static fr::String prefixes[] = {
            "Info",
            "Warn",
            "Error",
            "Assert",
        };

#ifdef WIN32
        fr::String delimiter = "Freight\\Source\\";
#elif __APPLE__
        fr::String delimiter = "Freight/Source/";
#endif
        
        fr::String line;
        line.append(TrimPath(filepath, delimiter))
            .append("[").append(std::to_string(lineNumber)).append("]: ")
            .append(message);

        std::lock_guard<std::mutex> lock(sMutex);

#ifdef WIN32
        static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

        switch (type)
        {
        case Logger::WARN:
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case Logger::ERR:
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        case Logger::ASSERT:
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        default:
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        }
#endif
        std::cout << "[" << prefixes[type] << "]";

#ifdef WIN32
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif

        std::cout << " " << line << std::endl;
    }
}
