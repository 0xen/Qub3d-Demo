#include <viking/vulkan/VulkanWindow.hpp>
#include "..\..\include\viking\vulkan\VulkanSwapchain.hpp"

using namespace viking::vulkan;

viking::vulkan::VulkanSwapchain::VulkanSwapchain(VulkanDevice* device, IVulkanSurface* surface)
{
	m_device = device;
	m_surface = surface;
	getSwapChainSupport(m_swap_chain_config);
}

viking::vulkan::VulkanSwapchain::~VulkanSwapchain()
{
}

void viking::vulkan::VulkanSwapchain::setupSwapchain()
{
	createSwapchain();
}

void viking::vulkan::VulkanSwapchain::destroySwapchain()
{
}

void viking::vulkan::VulkanSwapchain::createSwapchain()
{

}

void viking::vulkan::VulkanSwapchain::getSwapChainSupport(SwapChainConfiguration & support)
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
