#pragma once
#include "Freight.hpp"
#include "Freight/Math.hpp"


struct Vertex
{
    fr::Vec3 position;
};

struct Mesh
{
    Mesh(const std::vector<Vertex> &v, const std::vector<fr::u32> &i);
    ~Mesh();
    std::vector<Vertex> mVertices;
    std::vector<fr::u32> mIndices;
};

class GraphicsResourceManager
{
public:

    GraphicsResourceManager();
    ~GraphicsResourceManager();

    std::vector<std::shared_ptr<Mesh>> loadMeshes(const fr::Filepath &fp);

private:

    GraphicsResourceManager(const GraphicsResourceManager &) = delete;
    GraphicsResourceManager(GraphicsResourceManager &&) = delete;

};