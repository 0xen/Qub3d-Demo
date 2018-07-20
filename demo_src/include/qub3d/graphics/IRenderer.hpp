#pragma once

#include <qub3d/graphics/RenderingAPI.hpp>
#include <qub3d/IWindow.hpp>

#include <glm/glm.hpp>
#include <vector>

struct Mesh {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indices;
};

class IRenderer {
public:
    static IRenderer* loadRenderer(IWindow* window, RenderingAPI api);
    virtual void render() = 0;
protected:
    IRenderer();
private:
};
