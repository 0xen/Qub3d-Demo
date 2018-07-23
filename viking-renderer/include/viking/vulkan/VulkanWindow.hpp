#pragma once

/*
#include <cassert>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <qub3d\VulkanInstance.hpp>
#include <qub3d\IWindow.hpp>
#include <SDL_vulkan.h>
*/
namespace viking {
	namespace vulkan {
		class VulkanWindow
		{
		public:
			VulkanWindow();
			~VulkanWindow();
		private:
			//VkSurfaceKHR m_surface;
		};
	}
}