#include <viking/IWindow.hpp>
#include <viking/SDLWindow.hpp>

using namespace viking;

IWindow * viking::IWindow::createWindow(WindowDescriptor descriptor, WindowingAPI windowApi, RenderingAPI renderingApi)
{
	switch (windowApi)
	{
	case WindowingAPI::SDL:
		return SDLWindow::createWindow(descriptor,renderingApi);
		break;
	}
	return nullptr;
}

WindowingAPI viking::IWindow::GetWindowingAPI()
{
	return m_windowing_api;
}

viking::IWindow::IWindow(WindowingAPI windowing_api)
{
	m_windowing_api = windowing_api;
}
