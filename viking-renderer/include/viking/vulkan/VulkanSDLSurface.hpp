#pragma once
#include <viking/vulkan/IVulkanSurface.hpp>
#include <viking/SDLWindow.hpp>
#include <viking/IWindow.hpp>

namespace viking {
	namespace vulkan {
		class VulkanSDLSurface : public IVulkanSurface
		{
		public:
			virtual void initilizeSurface(IWindow* window, VkInstance& instance);
		};
	}
}