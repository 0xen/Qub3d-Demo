
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
}
