
#include <viking/vulkan/VulkanSDLWindow.hpp>

using namespace viking;
using namespace viking::vulkan;

VulkanSDLWindow::VulkanSDLWindow(WindowDescriptor descriptor) : SDLWindow(WindowingAPI::SDL)
{
	m_window = SDL_CreateWindow(
		descriptor.title,
		descriptor.windowposX, descriptor.windowposY,
		descriptor.width, descriptor.height,
		SDL_WINDOW_VULKAN
	);
	SDL_ShowWindow(m_window);
	m_running = true;

	SDL_Vulkan_GetInstanceExtensions(m_window, &m_extension_count, NULL);

	m_extentions = new const char *[m_extension_count];

	SDL_Vulkan_GetInstanceExtensions(m_window, &m_extension_count, m_extentions);
}
