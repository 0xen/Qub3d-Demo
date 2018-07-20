#pragma once
#include <qub3d\RenderingAPI.hpp>
#include <qub3d\IWindow.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

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
