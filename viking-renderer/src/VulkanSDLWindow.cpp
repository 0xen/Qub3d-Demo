
#include <viking/VulkanSDLWindow.hpp>

viking::VulkanSDLWindow::VulkanSDLWindow(WindowDescriptor descriptor)
{
	m_window = SDL_CreateWindow(
		descriptor.title,
		descriptor.windowposX, descriptor.windowposY,
		descriptor.width, descriptor.height,
		SDL_WINDOW_VULKAN
	);
	SDL_ShowWindow(m_window);
	m_running = true;
}
