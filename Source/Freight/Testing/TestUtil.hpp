#include <string>

namespace fr::Test
{
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