#include "FileLoader.hpp"
#include <cstdio>

namespace fr
{
    void LoadFileAsString(const fr::Filepath &fp, String &output)
    {
        FILE *f = fopen(fp.absolutePath().c_str(), "r");

        if (!f) {
            FR_WARN("Could not find file: " << fp.absolutePath());
            return;
        }

        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);

        output.resize(size);

        rewind(f);
        fread(&output[0], sizeof(char), size, f);
    }


    void LoadFileAsBytes(const fr::Filepath fp, std::vector<fr::u8> &output)
    {
        FILE *f = fopen(fp.absolutePath().c_str(), "rb");

        if (!f) {
            FR_WARN("Could not find file: " << fp.absolutePath());
            return;
        }

        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);

        output.resize(size);

        rewind(f);
        fread(&output[0], sizeof(fr::u8), size, f);
    }
}