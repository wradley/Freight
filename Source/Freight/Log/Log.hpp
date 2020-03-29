#pragma once
#include <sstream>
#include <mutex>
#include <stdlib.h>
#include "../Defines.hpp"
#include "../String.hpp"


#define FR_LOG(msg) {\
    fr::StringStream stream;\
    stream << msg;\
    fr::Logger::Log(fr::Logger::INFO, stream.str(), __FILE__, __LINE__);\
}

#define FR_WARN(msg) {\
    fr::StringStream stream;\
    stream << msg;\
    fr::Logger::Log(fr::Logger::WARN, stream.str(), __FILE__, __LINE__);\
}

#define FR_ERR(msg) {\
    fr::StringStream stream;\
    stream << msg;\
    fr::Logger::Log(fr::Logger::ERR, stream.str(), __FILE__, __LINE__);\
}

#define FR_ASSERT(condition, msg) if (!(condition)) {\
    fr::StringStream stream;\
    stream << msg;\
    fr::Logger::Log(fr::Logger::ASSERT, stream.str(), __FILE__, __LINE__);\
    abort();\
}

#define FR_CRASH(msg) { FR_ERR(msg); abort(); }

#ifdef FR_DEBUG_BUILD
#define FR_DEBUG_LOG(msg) FR_LOG(msg)
#define FR_DEBUG_WARN(msg) FR_WARN(msg)
#define FR_DEBUG_ERR(msg) FR_ERR(msg)
#define FR_DEBUG_ASSERT(condition, msg) FR_ASSERT(condition, msg)
#define FR_DEBUG_CRASH(msg) FR_CRASH(msg)
#else
#define FR_DEBUG_LOG(msg) 
#define FR_DEBUG_WARN(msg)
#define FR_DEBUG_ERR(msg)
#define FR_DEBUG_ASSERT(condition, msg)
#define FR_DEBUG_CRASH(msg)
#endif


namespace fr
{
    class Logger
    {
    public:

        enum Type
        {
            INFO = 0,
            WARN,
            ERR,
            ASSERT
        };

        static void Log(
            Type type,
            const fr::String &message,
            const fr::String &filepath,
            size_t lineNumber
        );

    private:

        static std::mutex sMutex;

    };
}
