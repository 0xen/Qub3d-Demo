#pragma once

#include <glm/glm.hpp>
#include <vector>

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

class GL11Renderer : public IRenderer {
public: 
    virtual void renderMesh(Mesh *mesh);
};
