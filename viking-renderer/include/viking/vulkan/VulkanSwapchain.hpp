#pragma once

#include <vulkan/vulkan.h>

#include <viking/vulkan/VulkanDevice.hpp>
#include <viking/vulkan/IVulkanSurface.hpp>
#include <viking/vulkan/VulkanSwapChainConfiguration.hpp>
#include <viking/vulkan/VulkanCommon.hpp>


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

			void createRenderPass();
			void destroyRenderPass();

			void createDepthImage();

			void createFrameBuffer();
			void destroyFrameBuffer();

			void createCommandBuffer();

			void createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView & view);

			void getSwapChainSupport(VulkanSwapChainConfiguration & support);
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_formats);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> available_present_modes);
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities);

			VkFormat getDepthImageFormat();
			VkFormat selectSutableFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

			VkImage m_depth_image;
			VkDeviceMemory m_depth_image_memory;
			VkImageView m_depth_image_view;

			VkSwapchainKHR m_swap_chain;
			std::vector<VkCommandBuffer> m_command_buffers;
			std::vector<VkImage> m_swap_chain_images;
			std::vector<VkFramebuffer> m_swap_chain_framebuffers;
			std::vector<VkImageView> m_swap_chain_image_views;
			VkRenderPass m_render_pass;
			VkFormat m_depth_image_format;

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