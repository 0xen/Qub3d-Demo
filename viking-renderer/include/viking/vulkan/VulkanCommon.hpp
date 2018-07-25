#pragma once

#include <vulkan/vulkan.h>

namespace viking {
	namespace vulkan {
		class VulkanDevice;
		struct VulkanCommon
		{
			static void createImage(VulkanDevice* device, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage & image, VkDeviceMemory & image_memory);
		
			static uint32_t findMemoryType(VulkanDevice* device, uint32_t type_filter, VkMemoryPropertyFlags properties);

			static void createImageView(VulkanDevice* device, VkImage image, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView & view);

			static VkCommandBuffer beginSingleTimeCommands(VulkanDevice* device, VkCommandPool command_pool);

			static void endSingleTimeCommands(VulkanDevice* device, VkCommandBuffer command_buffer, VkCommandPool command_pool);

			static void transitionImageLayout(VulkanDevice* device, VkImage image, VkFormat format, VkImageLayout old_layout, VkImageLayout new_layout);

			static bool hasStencilComponent(VkFormat format);


		
		};
	}
}