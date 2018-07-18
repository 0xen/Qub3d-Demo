#pragma once

#include <qub3d\BUILD_ORDER.hpp>

class IWindow
{
public:
	static IWindow* loadWindow(Settings::GameConfig* config, RenderingAPI api);
	void pollEvents();
	void swapBuffers();
	bool isRunning() { return m_running; };
	void sleep(float t);

	SDL_Window *getWindow() { return m_window; }

protected:
	SDL_Window * m_window;
	bool m_running;
	SDL_GLContext m_context;
private:
};