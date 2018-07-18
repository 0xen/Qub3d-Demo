#include <qub3d\BUILD_ORDER.hpp>

IRenderer * IRenderer::loadRenderer(RenderingAPI api)
{
	switch (api)
	{
	case GL11:
		return new GL11Renderer();
		break;
	case GL3:
		break;
	case Vulkan:
		return new VulkanRenderer();
		break;
	}
	return nullptr;
}
