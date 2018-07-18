#pragma once


#include <qub3d/IRenderer.hpp>

enum RenderingAPI
{
	GL11,
	GL3,
	Vulkan
};

struct Mesh {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indices;
};

class IRenderer {
public:
	static IRenderer* loadRenderer(RenderingAPI api);
	virtual void render() = 0;
protected:
	IRenderer();
private:
};
