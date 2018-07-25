#pragma once

#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>

namespace viking {
	namespace vulkan {
		struct VulkanQueueFamilyIndices
		{
			uint32_t graphics_indices = UINT32_MAX;
			uint32_t present_indices = UINT32_MAX;
			uint32_t compute_indices = UINT32_MAX;

			bool isComplete()
			{
				return graphics_indices < UINT32_MAX &&
					present_indices < UINT32_MAX &&
					compute_indices < UINT32_MAX;
			}

			void clear()
			{
				graphics_indices = UINT32_MAX;
				present_indices = UINT32_MAX;
				compute_indices = UINT32_MAX;
			}
		};
	}
}