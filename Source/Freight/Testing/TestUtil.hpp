#include <string>

#ifdef __APPLE__
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#elif WIN32
#include <windows.h>
#endif

namespace fr::Test
{
    inline void PrintPassed(const std::string &s) {
        std::cout << s << " - ";
#ifdef __APPLE__
        std::cout << GREEN << "Passed" << RESET << std::endl;
#elif WIN32
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << "Passed" << std::endl;
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
        std::cout << "Passed" << std::endl;
#endif
    }

    inline void PrintFailed(const std::string &s) {
        std::cout << s << " - ";
#ifdef __APPLE__
        std::cout << GREEN << "Failed" << RESET << std::endl;
#elif WIN32
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "Failed" << std::endl;
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
        std::cout << "Failed" << std::endl;
#endif
    }

    inline std::string FormatFileLineName(const char *file, int lineNumber, const char *name)
    {
        std::string f(file);
        std::string ret("[");
#ifdef WIN32
        ret.append(f.substr(f.rfind('\\', f.rfind('\\')-1)+1));
#else
        ret.append(f.substr(f.rfind('/', f.rfind('/')-1)+1));
#endif
        ret.append(": ");
        ret.append(std::to_string(lineNumber));
        ret.append("] ");
        ret.append(name);
        return ret;
    }

    inline std::string FormatLineName(int lineNumber, const char *name)
    {
        std::string ret("[");
        ret.append(std::to_string(lineNumber));
        ret.append("] ");
        ret.append(name);
        return ret;
    }
}