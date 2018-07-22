#include <viking/IRenderer.hpp>

using namespace viking;

IRenderer* Renderer::createRenderer(const API& api)
{
	switch(api)
	{
		case API::GL3: 
			return nullptr;

		case API::GL11:
			return nullptr;

		case API::Vulkan:
			return nullptr;
	}

	return nullptr;
}