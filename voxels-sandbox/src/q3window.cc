#include <qub3d/q3window.hpp>
#include <qub3d/q3shared_constants.hpp>

Q3Window::Q3Window(const char *title, int w, int h) : m_running(true)
{
    m_window = SDL_CreateWindow(
        "Qub3d",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_OPENGL);
    m_context = SDL_GL_CreateContext(m_window);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_ShowWindow(m_window);

#ifdef Q3_FULLSCREEN
    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
#endif
}

bool Q3Window::isRunning() { return m_running; }

void Q3Window::sleep(float t)
{
    SDL_Delay(static_cast<Uint32>(t));
}

void Q3Window::pollEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0)
    {
        if (e.type == SDL_QUIT)
            m_running = false;
    }
}

void Q3Window::swapBuffers()
{
    SDL_GL_SwapWindow(m_window);
}