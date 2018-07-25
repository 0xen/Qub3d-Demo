#include <viking/vulkan/VulkanCommon.hpp>

#include <viking/vulkan/VulkanDevice.hpp>

using namespace viking::vulkan;

void viking::vulkan::VulkanCommon::createImage(VulkanDevice* device, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage & image, VkDeviceMemory & image_memory)
{
	VkImageCreateInfo create_info = VulkanInitializers::imageCreateInfo(extent.width, extent.height, format, tiling, usage);
	bool sucsess = VulkanInitializers::validate(vkCreateImage(
		device->GetVulkanDevice(),
		&create_info,
		nullptr,
		&image
	));

	VkMemoryRequirements mem_requirements;
	vkGetImageMemoryRequirements(
		device->GetVulkanDevice(),
		image,
		&mem_requirements
	);

	VkMemoryAllocateInfo alloc_info = VulkanInitializers::memoryAllocateInfo(mem_requirements.size, findMemoryType(
		device,
		mem_requirements.memoryTypeBits,
		properties
	));

	sucsess = VulkanInitializers::validate(vkAllocateMemory(
		device->GetVulkanDevice(),
		&alloc_info,
		nullptr,
		&image_memory
	));

	vkBindImageMemory(
		device->GetVulkanDevice(),
		image,
		image_memory,
		0
	);
}

uint32_t viking::vulkan::VulkanCommon::findMemoryType(VulkanDevice* device, uint32_t type_filter, VkMemoryPropertyFlags properties)
{
	for (uint32_t i = 0; i < device->GetPhysicalDevice().getPhysicalDeviceMemoryProperties()->memoryTypeCount; i++)
	{
		if (type_filter & (1 << i) &&
			(device->GetPhysicalDevice().getPhysicalDeviceMemoryProperties()->memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}
	return -1;
}

void viking::vulkan::VulkanCommon::createImageView(VulkanDevice* device, VkImage image, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView & view)
{
	VkImageViewCreateInfo create_info = VulkanInitializers::imageViewCreate(image, format, aspect_flags);
	bool sucsess = VulkanInitializers::validate(vkCreateImageView(
		device->GetVulkanDevice(),
		&create_info,
		nullptr,
		&view
	));
}

VkCommandBuffer viking::vulkan::VulkanCommon::beginSingleTimeCommands(VulkanDevice* device, VkCommandPool command_pool)
{
	VkCommandBufferAllocateInfo alloc_info = VulkanInitializers::commandBufferAllocateInfo(
		command_pool,
		1
	);
	VkCommandBuffer command_buffer;
	bool sucsess = VulkanInitializers::validate(vkAllocateCommandBuffers(
		device->GetVulkanDevice(),
		&alloc_info,
		&command_buffer
	));
	VkCommandBufferBeginInfo begin_info = VulkanInitializers::commandBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
	sucsess = VulkanInitializers::validate(vkBeginCommandBuffer(
		command_buffer,
		&begin_info
	));
	return command_buffer;
}

void viking::vulkan::VulkanCommon::endSingleTimeCommands(VulkanDevice * device, VkCommandBuffer command_buffer, VkCommandPool command_pool)
{
	vkEndCommandBuffer(command_buffer);
	VkSubmitInfo submit_info = VulkanInitializers::submitInfo(command_buffer);
	vkQueueSubmit(
		*device->GetGraphicsQueue(),
		1,
		&submit_info,
		VK_NULL_HANDLE
	);
	vkQueueWaitIdle(
		*device->GetGraphicsQueue()
	);
	vkFreeCommandBuffers(
		device->GetVulkanDevice(),
		command_pool,
		1,
		&command_buffer
	);
}

void viking::vulkan::VulkanCommon::transitionImageLayout(VulkanDevice * device, VkImage image, VkFormat format, VkImageLayout old_layout, VkImageLayout new_layout)
{
	VkCommandBuffer command_buffer = beginSingleTimeCommands(device, *device->GetGraphicsCommandPool());

	VkImageMemoryBarrier barrier = VulkanInitializers::imageMemoryBarrier(image, format, old_layout, new_layout);

	vkCmdPipelineBarrier(
		command_buffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		0,
		0,
		nullptr,
		0,
		nullptr,
		1,
		&barrier
	);

	endSingleTimeCommands(device, command_buffer, *device->GetGraphicsCommandPool());
}

bool viking::vulkan::VulkanCommon::hasStencilComponent(VkFormat format)
{
	return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}
