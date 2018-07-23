#include <viking/SDLWindow.hpp>
#include <viking/VulkanSDLWindow.hpp>

using namespace viking;

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