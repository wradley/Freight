#pragma once
#include "Freight.hpp"

class LevelLoader
{
public:

    LevelLoader(std::shared_ptr<fr::EventManager> em);
    ~LevelLoader();

    void load(const fr::Filepath &filename);

private:

    std::shared_ptr<fr::EventManager> mEventManager;

private:

    LevelLoader(const LevelLoader &) = delete;
    LevelLoader(LevelLoader &&) = delete;

};