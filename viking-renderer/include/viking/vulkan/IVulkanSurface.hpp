#pragma once

#include <viking/IWindow.hpp>
#include <viking/vulkan/VulkanInstance.hpp>
#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>

namespace viking {
	namespace vulkan {
		class IVulkanSurface
		{
		public:
			virtual void initilizeSurface(IWindow* window, VkInstance& instance) = 0;
			VkSurfaceKHR& GetSurface();
		protected:
			VkSurfaceKHR m_surface;
		};
	}
}