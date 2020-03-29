#pragma once
#include "../String.hpp"

namespace fr
{
    // realative filepath from asset directory
    class Filepath
    {
    public:

        static void SetPathToBaseDir(const String &basePath);

        Filepath();
        Filepath(const char *relativePath);
        Filepath(const String &relativePath);
        Filepath(const Filepath &fp);
        Filepath(Filepath &&fp);
        Filepath& operator= (const char *relativePath);
        Filepath& operator= (const String &relativePath);
        Filepath& operator= (const Filepath &fp);
        ~Filepath();

        void clear();

        String absolutePath() const;

        friend std::ostream &operator<< (std::ostream &os, const Filepath &fp);

    private:

        static String sPathToBaseDir;
        String mPath;

    };
}