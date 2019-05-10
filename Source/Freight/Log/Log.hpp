#pragma once
#include <string>
#include <sstream>
#include <cstdlib>
#define UNICODE
#include <windows.h>

#define FR8_FILE_LINE "[" << __FILEW__ << " " << __LINE__ << "]"

#define FR8_LOG(msg) {                                               \
    std::wstringstream stream;                                       \
    stream << L"[Log] " << FR8_FILE_LINE << " " << msg << "\n";      \
    FR8::LOG::Write(stream.str());                                   \
}

#define FR8_WARN(msg) {                                              \
    std::wstringstream stream;                                       \
    stream << L"[Warning] " << FR8_FILE_LINE << " " << msg << "\n";  \
    FR8::LOG::Write(stream.str());                                   \
}

#define FR8_ERROR(msg) {                                             \
    std::wstringstream stream;                                       \
    stream << L"[Error] " << FR8_FILE_LINE << " " << msg << "\n";    \
    FR8::LOG::Write(stream.str());                                   \
}

#define FR8_ASSERT(condition, msg) if (!condition) {                 \
    std::wstringstream stream;                                       \
    stream << L"[Error] " << FR8_FILE_LINE << " " << msg << "\n";    \
    FR8::LOG::Write(stream.str());                                   \
    quick_exit(EXIT_FAILURE);                                        \
}


#ifdef NDEBUG
#define FR8_DBG_LOG(msg) {}
#define FR8_DBG_WARN(msg) {}
#define FR8_DBG_ERROR(msg) {}
#define FR8_DBG_ASSERT(condition, msg) {}
#else
#define FR8_DBG_LOG(msg) FR8_LOG(msg)
#define FR8_DBG_WARN(msg) FR8_WARN(msg)
#define FR8_DBG_ERROR(msg) FR8_ERROR(msg)
#define FR8_DBG_ASSERT(condition, msg) FR8_ASSERT(condition, msg)
#endif // DEBUG


namespace FR8::LOG
{
#ifdef WIN32
    inline void Write(const std::wstring &str)
    {
        OutputDebugStringW(str.c_str());
    }
#endif
}