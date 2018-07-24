#include <viking/SDLWindow.hpp>
#include <viking/IRenderer.hpp>
#include <viking/vulkan/VulkanSDLWindow.hpp>

int main(int argc, char **argv)
{
    using namespace viking;

	const RenderingAPI renderingApi = RenderingAPI::Vulkan;
	const WindowingAPI windowApi = WindowingAPI::SDL;

	IWindow* window = IWindow::createWindow(WindowDescriptor("Qub3d Demo", 800, 600), windowApi, renderingApi);

    IRenderer *renderer = IRenderer::createRenderer(renderingApi);
	renderer->addWindow(window);
	renderer->start();


	while (window->isRunning())
	{
		window->poll();
		window->swapBuffers();
	}

	delete window;

    return 0;
}
