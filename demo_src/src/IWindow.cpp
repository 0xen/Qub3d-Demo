#include <qub3d\BUILD_ORDER.hpp>

void IWindow::sleep(float t)
{
    SDL_Delay(static_cast<Uint32>(t));
}

void IWindow::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0)
    {
        if (event.type == SDL_QUIT)
            m_running = false;
    }
}

void IWindow::swapBuffers()
{
    SDL_GL_SwapWindow(m_window);
}