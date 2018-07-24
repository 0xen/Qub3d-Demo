#include <viking/vulkan/VulkanSDLSurface.hpp>
#include <viking/vulkan/VulkanInstance.hpp>
#include <viking/IWindow.hpp>
#include <SDL.h>
#include <SDL_syswm.h>
#include <assert.h>

using namespace viking;
using namespace viking::vulkan;

void VulkanSDLSurface::initilizeSurface(IWindow* window, VkInstance & instance)
{
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	SDLWindow* sdl_window = static_cast<SDLWindow*>(window);
	assert(SDL_GetWindowWMInfo(sdl_window->GetSDLWindow(), &info) == SDL_TRUE);

	VkWin32SurfaceCreateInfoKHR w32sci = {};
	w32sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	w32sci.pNext = NULL;
	w32sci.hinstance = GetModuleHandle(NULL);
	w32sci.hwnd = info.info.win.window;

	assert(vkCreateWin32SurfaceKHR(
		instance,
		&w32sci,
		nullptr,
		&m_surface) == VK_SUCCESS);
}