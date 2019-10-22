#pragma once
#include "Freight.hpp"
#include "GraphicsResourceManager.hpp"
#include "glad/glad.h"

class GraphicsSystem
{
public:

    GraphicsSystem();
    ~GraphicsSystem();

    void start(std::shared_ptr<fr::EventManager> em);
    void update(std::shared_ptr<fr::EventManager> em);
    void stop();

private:

    GraphicsResourceManager mResourceManager;
    GLuint VAO, VBO, EBO, SHADERPROG;
    size_t NUM_INDICES;


};