#include <qub3d\GL11Window.hpp>

GL11Window::GL11Window(const char *title, int w, int h)
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
    m_running = true;
}