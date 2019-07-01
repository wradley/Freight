#include "Log.hpp"
#include <iostream>

namespace FR8
{
    std::mutex Logger::sMutex;
    wchar_t Logger::sBuffer[Logger::BUFFER_SIZE];
    size_t Logger::sIndex = 0;

    // TODO: make constexpr
    std::wstring TrimPath(const std::wstring &filepath, const std::wstring delimiter)
    {
        auto index = filepath.find(delimiter);
        if (index != std::wstring::npos) {
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
        const std::wstring &prefix,
        const std::wstring &message,
        const std::wstring &filepath,
        size_t lineNumber
    ){
        // "[<prefix>] "  "<filepath>"  "[<lineNumber>]: "  "<message>" "\n"

#ifdef WIN32
        std::wstring delimiter = L"Freight\\Source\\";
#elif __APPLE__
        std::wstring delimiter = L"Freight/Source/";
#endif
        
        std::wstring line;
        line.append(L"[").append(prefix).append(L"] ")
            .append(TrimPath(filepath, delimiter))
            .append(L"[").append(std::to_wstring(lineNumber)).append(L"]: ")
            .append(message).append(L"\n");

        std::lock_guard<std::mutex> lock(sMutex);

        size_t lineIndex = 0;
        while (line.size() - lineIndex > 0) {
            size_t spaceLeft = BUFFER_SIZE - (sIndex + 1);
            size_t copyAmount = spaceLeft <= line.size() - lineIndex ? spaceLeft : line.size() - lineIndex;
            CopyToBuffer(&sBuffer[sIndex], &line[lineIndex], copyAmount);
            lineIndex += copyAmount;
            sIndex += copyAmount;

            if (sIndex + 1 == BUFFER_SIZE)
                LocklessFlush();
        }
    }


    void Logger::Flush()
    {
        std::lock_guard<std::mutex> lock(sMutex);
        LocklessFlush();
    }


    void Logger::LocklessFlush()
    {
        sBuffer[sIndex] = 0;
        std::wcout << sBuffer;
        sIndex = 0;
    }
}
