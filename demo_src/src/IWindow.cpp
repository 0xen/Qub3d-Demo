#include <qub3d\IWindow.hpp>
#include <qub3d\GL11Window.hpp>
#include <qub3d\VulkanWindow.hpp>

void IWindow::sleep(float t)
{
    SDL_Delay(static_cast<Uint32>(t));
}

IWindow * IWindow::loadWindow(Settings::GameConfig * config, RenderingAPI api)
{
    switch (api)
    {
    case GL11:
        return new GL11Window("Qub3d", config->WindowWidth, config->WindowHeight);
        break;
    case GL3:
        break;
    case Vulkan:
        return new VulkanWindow("Qub3d", config->WindowWidth, config->WindowHeight);
        break;
    }
    return nullptr;
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