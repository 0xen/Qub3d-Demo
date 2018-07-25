#pragma once
#include <viking/WindowDescriptor.hpp>
#include <viking/API.hpp>

namespace viking
{
	class IWindow
	{
	public:
		static IWindow* createWindow(WindowDescriptor descriptor, WindowingAPI windowApi,RenderingAPI renderingApi);
		virtual void poll() = 0;
		virtual void swapBuffers() = 0;
		virtual bool isRunning() = 0;
		virtual void GetSize(int& width, int& height) = 0;
		WindowingAPI GetWindowingAPI();
	protected:
		IWindow(WindowingAPI windowing_api);
	private:
		WindowingAPI m_windowing_api;
	};
}