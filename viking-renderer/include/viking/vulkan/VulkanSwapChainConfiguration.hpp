#pragma once

#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>
#include <vector>

namespace viking {
	namespace vulkan {
		struct VulkanSwapChainConfiguration
		{
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> present_modes;
		};
	}
}