#pragma once

#include <viking/vulkan/VulkanDevice.hpp>
#include <viking/vulkan/IVulkanSurface.hpp>
#include <viking/vulkan/VulkanSwapChainConfiguration.hpp>

#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>

namespace viking {
	namespace vulkan {
		class VulkanSwapchain
		{
		public:
			VulkanSwapchain(VulkanDevice* device,IWindow* window, IVulkanSurface* surface);
			~VulkanSwapchain();
		private:
			void initSwapchain();
			void deinitSwapchain();

			void createSwapchain();
			void destroySwapchain();

			void createSwapchainImages();
			void destroySwapchainImages();

			void createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView & view);

			void getSwapChainSupport(VulkanSwapChainConfiguration & support);
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_formats);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> available_present_modes);
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities);

			VkSwapchainKHR m_swap_chain;
			std::vector<VkImage> m_swap_chain_images;
			std::vector<VkImageView> m_swap_chain_image_views;

			VulkanSwapChainConfiguration m_swap_chain_config;
			VkSurfaceFormatKHR m_surface_format;
			VkExtent2D m_extent;
			VkPresentModeKHR m_present_mode;
			IVulkanSurface* m_surface;
			VulkanDevice* m_device;
			IWindow* m_window;
		};
	}
}