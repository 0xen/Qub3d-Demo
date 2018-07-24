#pragma once

#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>

namespace viking {
	namespace vulkan {
		class VulkanWindow
		{
		public:
			VulkanWindow();
			~VulkanWindow();
			const char** getExtensions();
			unsigned int getExtensionsCount();
		protected:
			uint32_t m_extension_count;
			const char** m_extentions = NULL;
			VkSurfaceKHR m_surface;
		};
	}
}