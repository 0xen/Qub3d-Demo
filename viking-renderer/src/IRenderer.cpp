#include <viking/IRenderer.hpp>

using namespace viking;

IRenderer* IRenderer::createRenderer(const RenderingAPI& api)
{
	switch(api)
	{
		case RenderingAPI::GL3: 
			return nullptr;

		case RenderingAPI::GL11:
			return nullptr;

		case RenderingAPI::Vulkan:
			return nullptr;
	}

	return nullptr;
}
