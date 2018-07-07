#pragma once

#include <SDL.h>

class Q3Window {
public:
    Q3Window(const char *title, int w, int h);

    void pollEvents();
    void swapBuffers();
    bool isRunning();
    void sleep(float t);

    SDL_Window *getWindow() { return m_window; }

private:
    SDL_Window * m_window;
    SDL_GLContext m_context;

    bool m_running;
};