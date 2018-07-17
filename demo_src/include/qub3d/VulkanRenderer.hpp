#pragma once
#include <qub3d\BUILD_ORDER.hpp>

class VulkanRenderer : public IRenderer
{
public:
	virtual void renderMesh(Mesh *mesh);
};
