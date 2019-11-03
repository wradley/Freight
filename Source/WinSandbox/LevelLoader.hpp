#pragma once
#include "Freight.hpp"

class LevelLoader
{
public:

    LevelLoader();
    ~LevelLoader();

    void load(const fr::Filepath &filename);

private:

    LevelLoader(const LevelLoader &) = delete;
    LevelLoader(LevelLoader &&) = delete;

};