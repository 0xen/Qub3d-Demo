#include <viking/SDLWindow.hpp>
#include <viking/vulkan/VulkanSDLWindow.hpp>

using namespace viking;
using namespace viking::vulkan;

viking::SDLWindow::~SDLWindow()
{
	SDL_DestroyWindow(m_window);
}

SDLWindow * viking::SDLWindow::createWindow(WindowDescriptor descriptor, RenderingAPI api)
{
	switch (api)
	{
	case RenderingAPI::Vulkan:

		return new VulkanSDLWindow(descriptor);
		break;
	}
	return nullptr;
}

void SDLWindow::poll()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) > 0)
	{
		if (event.type == SDL_QUIT)
			m_running = false;
	}
}

void SDLWindow::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

bool SDLWindow::isRunning()
{
	return m_running;
}

void SDLWindow::GetSize(int & width, int & height)
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(m_window), &DM);
	width = DM.w;
	height = DM.h;
}

SDL_Window * viking::SDLWindow::GetSDLWindow()
{
	return m_window;
}

viking::SDLWindow::SDLWindow(WindowingAPI windowing_api) : IWindow(windowing_api) {}
