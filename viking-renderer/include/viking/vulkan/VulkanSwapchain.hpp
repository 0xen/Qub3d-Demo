#pragma once

#include <viking/vulkan/VulkanDevice.hpp>
#include <viking/vulkan/IVulkanSurface.hpp>

#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>

namespace viking {
	namespace vulkan {
		struct SwapChainConfiguration
		{
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> present_modes;
		};


		class VulkanSwapchain
		{
		public:
			VulkanSwapchain(VulkanDevice* device, IVulkanSurface* surface);
			~VulkanSwapchain();
		private:
			void setupSwapchain();
			void destroySwapchain();

			void createSwapchain();

			void getSwapChainSupport(SwapChainConfiguration & support);

			SwapChainConfiguration m_swap_chain_config;
			IVulkanSurface* m_surface;
			VulkanDevice* m_device;
		};
	}
}