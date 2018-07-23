#include <viking/IRenderer.hpp>
#include <viking/vulkan/VulkanRenderer.hpp>

using namespace viking;

IRenderer* IRenderer::createRenderer(IWindow* window, const RenderingAPI& api)
{
	switch(api)
	{
		case RenderingAPI::GL3: 
			return nullptr;

		case RenderingAPI::GL11:
			return nullptr;

		case RenderingAPI::Vulkan:
			return new vulkan::VulkanRenderer(window);
	}

	return nullptr;
}
