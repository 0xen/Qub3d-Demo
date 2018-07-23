#pragma once

#include <SDL.h>
#include <SDL_syswm.h>

#include <viking/WindowDescriptor.hpp>
#include <viking/IWindow.hpp>

namespace viking
{
	class SDLWindow : public IWindow
	{
	public:
		~SDLWindow();
		static SDLWindow* createWindow(WindowDescriptor descriptor, RenderingAPI api);
		virtual void poll();
		virtual void swapBuffers();
		virtual bool isRunning();
	protected:
		SDLWindow(WindowingAPI windowing_api);
		SDL_Window * m_window;
		SDL_GLContext m_context;
		bool m_running;
	private:

	};
}