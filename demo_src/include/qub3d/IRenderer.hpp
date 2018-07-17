#pragma once


#include <qub3d/IRenderer.hpp>

struct Mesh {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indices;
};

class IRenderer {
public:
    virtual void renderMesh(Mesh *mesh) = 0;
private:
};
