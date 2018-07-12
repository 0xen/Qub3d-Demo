#include <qub3d/window.hpp>
#include <qub3d/settings.hpp>

Window::Window(const char *title, int w, int h) : m_running(true)
{
    m_window = SDL_CreateWindow(
        "Qub3d Demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w,
        h,
        SDL_WINDOW_OPENGL);

    m_context = SDL_GL_CreateContext(m_window);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    SDL_ShowWindow(m_window);
}

void Window::sleep(float t)
{
    SDL_Delay(static_cast<Uint32>(t));
}

void Window::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0)
    {
        if (event.type == SDL_QUIT)
            m_running = false;
    }
}

void Window::swapBuffers()
{
    SDL_GL_SwapWindow(m_window);
}