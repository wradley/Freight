#include "Filepath.hpp"


namespace fr
{
#ifdef WIN32
    String Filepath::sPathToBaseDir("C:");
#endif

    void Filepath::SetPathToBaseDir(const String &fp)
    {
        sPathToBaseDir = fp;
    }


    Filepath::Filepath()
    {}


    Filepath::Filepath(const char *relativePath) : mPath(relativePath)
    {}


    Filepath::Filepath(const String &relativePath) : mPath(relativePath)
    {}


    Filepath::Filepath(const Filepath &fp) : mPath(fp.mPath)
    {}


    Filepath::Filepath(Filepath &&fp) : mPath(std::move(fp.mPath))
    {}


    Filepath &Filepath::operator=(const char *relativePath)
    {
        mPath = relativePath;
        return *this;
    }


    Filepath &Filepath::operator= (const String &relativePath)
    {
        mPath = relativePath;
        return *this;
    }


    Filepath &Filepath::operator= (const Filepath &fp)
    {
        mPath = fp.mPath;
        return *this;
    }


    Filepath::~Filepath()
    {}


    void Filepath::clear()
    {
        mPath.clear();
    }


    String Filepath::absolutePath() const
    {
        return String(sPathToBaseDir).append("/").append(mPath);
    }


    std::ostream& operator<< (std::ostream &os, const Filepath &fp)
    {
        return os << Filepath::sPathToBaseDir << "/" << fp.mPath;
    }
}