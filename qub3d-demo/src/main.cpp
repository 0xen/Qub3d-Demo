#include <viking/WindowDescriptor.hpp>
#include <viking/SDLWindow.hpp>
//#include <viking/IRenderer.hpp>

int main(int argc, char **argv)
{
    using namespace viking;

	const RenderingAPI renderingApi = RenderingAPI::Vulkan;
	const WindowingAPI windowApi = WindowingAPI::SDL;

   //SDL_Window *window = SDLWindowProvider::createWindow(WindowDescriptor("Qub3d Demo", 800, 600), renderingApi);

    //IRenderer *renderer = IRenderer::createRenderer(renderingApi);
    
	SDLWindow* window = (SDLWindow*)IWindow::createWindow(WindowDescriptor("Qub3d Demo", 800, 600), windowApi,renderingApi);

	while (window->isRunning())
	{
		window->poll();
		window->swapBuffers();
	}

	delete window;

    return 0;
}
