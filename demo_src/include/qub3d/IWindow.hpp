#pragma once

#include <qub3d\RenderingAPI.hpp>
#include <qub3d\settings.hpp>
#include <SDL.h>
#include <SDL_syswm.h>


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