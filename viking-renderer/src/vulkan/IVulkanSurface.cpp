#include <viking/vulkan/IVulkanSurface.hpp>

using namespace viking::vulkan;

VkSurfaceKHR & viking::vulkan::IVulkanSurface::GetSurface()
{
	return m_surface;
}
