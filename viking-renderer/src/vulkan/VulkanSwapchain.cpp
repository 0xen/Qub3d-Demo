#include <viking/vulkan/VulkanSwapchain.hpp>

using namespace viking::vulkan;

viking::vulkan::VulkanSwapchain::VulkanSwapchain(VulkanDevice* device, IWindow* window, IVulkanSurface* surface)
{
	m_device = device;
	m_window = window;
	m_surface = surface;
	getSwapChainSupport(m_swap_chain_config);
	m_surface_format = chooseSwapSurfaceFormat(m_swap_chain_config.formats);
	m_present_mode = chooseSwapPresentMode(m_swap_chain_config.present_modes);
	initSwapchain();
	createCommandBuffer();
}

viking::vulkan::VulkanSwapchain::~VulkanSwapchain()
{
	deinitSwapchain();
}

void viking::vulkan::VulkanSwapchain::initSwapchain()
{
	createSwapchain();
	createSwapchainImages();
	createRenderPass();
	createDepthImage();
	createFrameBuffer();
}

void viking::vulkan::VulkanSwapchain::deinitSwapchain()
{
	destroyFrameBuffer();
	destroyRenderPass();
	destroySwapchainImages();
	destroySwapchain();
}

void viking::vulkan::VulkanSwapchain::createSwapchain()
{
	m_extent = chooseSwapExtent(m_swap_chain_config.capabilities);

	uint32_t image_count = m_swap_chain_config.capabilities.minImageCount + 1;

	if (m_swap_chain_config.capabilities.maxImageCount > 0 && image_count > m_swap_chain_config.capabilities.maxImageCount)
		image_count = m_swap_chain_config.capabilities.maxImageCount;

	VulkanQueueFamilyIndices* indices = m_device->GetPhysicalDevice().getQueueFamilies();
	VkSwapchainCreateInfoKHR create_info = VulkanInitializers::swapchainCreateInfoKHR(
		m_surface_format,
		m_extent,
		m_present_mode,
		image_count,
		m_surface->GetSurface(),
		*indices,
		m_swap_chain_config
	);

	bool sucsess = VulkanInitializers::validate(vkCreateSwapchainKHR(
		m_device->GetVulkanDevice(),
		&create_info,
		nullptr,
		&m_swap_chain
	));

	sucsess = VulkanInitializers::validate(vkGetSwapchainImagesKHR(
		m_device->GetVulkanDevice(),
		m_swap_chain,
		&image_count,
		nullptr
	));

	m_swap_chain_images.resize(image_count);


	sucsess = VulkanInitializers::validate(vkGetSwapchainImagesKHR(
		m_device->GetVulkanDevice(),
		m_swap_chain,
		&image_count,
		m_swap_chain_images.data()
	));
}

void viking::vulkan::VulkanSwapchain::destroySwapchain()
{
	vkDestroySwapchainKHR(
		m_device->GetVulkanDevice(),
		m_swap_chain,
		nullptr
	);
}

void viking::vulkan::VulkanSwapchain::createSwapchainImages()
{
	m_swap_chain_image_views.resize(m_swap_chain_images.size());
	int i = 0;
	for (auto swapchain_image : m_swap_chain_images)
	{
		createImageView(swapchain_image, m_surface_format.format, VK_IMAGE_ASPECT_COLOR_BIT, m_swap_chain_image_views[i]);
		i++;
	}
}

void viking::vulkan::VulkanSwapchain::destroySwapchainImages()
{
	for (uint32_t i = 0; i < m_swap_chain_image_views.size(); i++)
	{
		vkDestroyImageView(
			m_device->GetVulkanDevice(),
			m_swap_chain_image_views[i],
			nullptr
		);
	}
	m_swap_chain_image_views.clear();
}

void viking::vulkan::VulkanSwapchain::createRenderPass()
{
	std::vector<VkAttachmentDescription> attachments = {
		VulkanInitializers::attachmentDescription(m_surface_format.format, VK_ATTACHMENT_STORE_OP_STORE,VK_IMAGE_LAYOUT_PRESENT_SRC_KHR),
		VulkanInitializers::attachmentDescription(getDepthImageFormat(), VK_ATTACHMENT_STORE_OP_DONT_CARE,VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
	};

	VkAttachmentReference color_attachment_refrence = VulkanInitializers::attachmentReference(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, 0);
	VkAttachmentReference depth_attachment_refrence = VulkanInitializers::attachmentReference(VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1);
	VkSubpassDescription subpass = VulkanInitializers::subpassDescription(color_attachment_refrence, depth_attachment_refrence);
	VkSubpassDependency subpass_dependency = VulkanInitializers::subpassDependency();
	VkRenderPassCreateInfo render_pass_info = VulkanInitializers::renderPassCreateInfo(attachments, subpass, subpass_dependency);

	bool sucsess = VulkanInitializers::validate(vkCreateRenderPass(
		m_device->GetVulkanDevice(),
		&render_pass_info,
		nullptr,
		&m_render_pass
	));

}

void viking::vulkan::VulkanSwapchain::destroyRenderPass()
{
	vkDestroyRenderPass(
		m_device->GetVulkanDevice(),
		m_render_pass,
		nullptr);
}

void viking::vulkan::VulkanSwapchain::createDepthImage()
{
	m_depth_image_format = getDepthImageFormat();
	VulkanCommon::createImage(m_device, m_extent, m_depth_image_format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_depth_image, m_depth_image_memory);
	VulkanCommon::createImageView(m_device, m_depth_image, m_depth_image_format, VK_IMAGE_ASPECT_DEPTH_BIT, m_depth_image_view);

	VulkanCommon::transitionImageLayout(m_device, m_depth_image, m_depth_image_format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

void viking::vulkan::VulkanSwapchain::createFrameBuffer()
{
	m_swap_chain_framebuffers.resize(m_swap_chain_image_views.size());
	for (uint32_t i = 0; i < m_swap_chain_image_views.size(); i++)
	{
		// What 
		std::vector<VkImageView> attachments = {
			m_swap_chain_image_views[i],
			m_depth_image_view
		};
		// Frame buffer create info
		VkFramebufferCreateInfo framebuffer_info = VulkanInitializers::framebufferCreateInfo(m_extent, attachments, m_render_pass);

		bool sucsess = VulkanInitializers::validate(vkCreateFramebuffer(
			m_device->GetVulkanDevice(),
			&framebuffer_info,
			nullptr,
			&m_swap_chain_framebuffers[i]
		));
	}
}

void viking::vulkan::VulkanSwapchain::destroyFrameBuffer()
{
	for (auto framebuffer : m_swap_chain_framebuffers)
	{
		vkDestroyFramebuffer(
			m_device->GetVulkanDevice(),
			framebuffer,
			nullptr
		);
	}
}

void viking::vulkan::VulkanSwapchain::createCommandBuffer()
{
	m_command_buffers.resize(m_swap_chain_framebuffers.size());
	VkCommandBufferAllocateInfo alloc_info = VulkanInitializers::commandBufferAllocateInfo(
		*m_device->GetGraphicsCommandPool(),
		static_cast<uint32_t>(m_command_buffers.size())
	);
	bool sucsess = VulkanInitializers::validate(vkAllocateCommandBuffers(
		m_device->GetVulkanDevice(),
		&alloc_info,
		m_command_buffers.data()
	));
}

void viking::vulkan::VulkanSwapchain::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView & view)
{
	VkImageViewCreateInfo create_info = VulkanInitializers::imageViewCreate(image, format, aspect_flags);
	bool sucsess = VulkanInitializers::validate(vkCreateImageView(
		m_device->GetVulkanDevice(),
		&create_info,
		nullptr,
		&view
	)); 
}

void viking::vulkan::VulkanSwapchain::getSwapChainSupport(VulkanSwapChainConfiguration & support)
{
	bool sucsess = VulkanInitializers::validate(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
		m_device->GetPhysicalDevice().GetPhysicalDevice(),
		m_surface->GetSurface(),
		&support.capabilities
	));

	uint32_t format_count = 0;
	sucsess = VulkanInitializers::validate(vkGetPhysicalDeviceSurfaceFormatsKHR(
		m_device->GetPhysicalDevice().GetPhysicalDevice(),
		m_surface->GetSurface(),
		&format_count, 
		nullptr
	));

	if (format_count == 0) return;

	support.formats.resize(format_count);
	sucsess = VulkanInitializers::validate(vkGetPhysicalDeviceSurfaceFormatsKHR(
		m_device->GetPhysicalDevice().GetPhysicalDevice(),
		m_surface->GetSurface(),
		&format_count,
		support.formats.data()
	));

	uint32_t present_mode_count;
	sucsess = VulkanInitializers::validate(vkGetPhysicalDeviceSurfacePresentModesKHR(
		m_device->GetPhysicalDevice().GetPhysicalDevice(),
		m_surface->GetSurface(),
		&present_mode_count,
		nullptr
	));

	if (present_mode_count == 0) return;
	support.present_modes.resize(present_mode_count);

	sucsess = VulkanInitializers::validate(vkGetPhysicalDeviceSurfacePresentModesKHR(
		m_device->GetPhysicalDevice().GetPhysicalDevice(),
		m_surface->GetSurface(),
		&present_mode_count,
		support.present_modes.data()
	));

}

VkSurfaceFormatKHR VulkanSwapchain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& available_formats)
{
	if (available_formats.size() == 1 && available_formats[0].format == VK_FORMAT_UNDEFINED)
	{
		return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}
	for (const auto& format : available_formats)
	{
		if (format.format == VK_FORMAT_B8G8R8A8_UNORM && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return format;
		}
	}
	if (available_formats.size() > 0)return available_formats[0];

	return{ VK_FORMAT_UNDEFINED };
}

VkPresentModeKHR VulkanSwapchain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> available_present_modes)
{
	for (const auto& available_present_mode : available_present_modes)
	{
		if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
			return available_present_mode;
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities)
{
	if (capabilities.currentExtent.width != UINT32_MAX)
	{
		return capabilities.currentExtent;
	}
	else
	{
		int width, height;
		m_window->GetSize(width, height);
		VkExtent2D extent = { (uint32_t)width, (uint32_t)height };
		if (extent.width > capabilities.maxImageExtent.width)extent.width = capabilities.maxImageExtent.width;
		if (extent.width < capabilities.minImageExtent.width)extent.width = capabilities.minImageExtent.width;
		if (extent.height > capabilities.maxImageExtent.width)extent.height = capabilities.maxImageExtent.height;
		if (extent.height < capabilities.minImageExtent.width)extent.height = capabilities.minImageExtent.height;
		return extent;
	}
}

VkFormat viking::vulkan::VulkanSwapchain::getDepthImageFormat()
{
	return selectSutableFormat(
		{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}

VkFormat viking::vulkan::VulkanSwapchain::selectSutableFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
	for (VkFormat format : candidates)
	{
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(m_device->GetPhysicalDevice().GetPhysicalDevice(), format, &props);
		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
		{
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
		{
			return format;
		}
	}
	return VK_FORMAT_UNDEFINED;
}
