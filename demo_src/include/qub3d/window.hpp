#pragma once

#include <SDL.h>

class Window
{
  public:
    Window(const char *title, int w, int h);

    void pollEvents();
    void swapBuffers();
    bool isRunning() { return m_running; };
    void sleep(float t);

    SDL_Window *getWindow() { return m_window; }

  private:
    
    SDL_Window *m_window;
    SDL_GLContext m_context;

    bool m_running;
};