#include <qub3d\IWindow.hpp>
#include <qub3d\GL11Window.hpp>

#ifdef QUB3D_HAS_VULKAN_SDK
    #include <qub3d\VulkanWindow.hpp>
#endif

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
#ifdef QUB3D_HAS_VULKAN_SDK
        return new VulkanWindow("Qub3d", config->WindowWidth, config->WindowHeight);
#else
        // TODO: Fallthrough for no vulkan window support. Cheat and use GL11 for now.
        return new GL11Window("Qub3d", config->WindowWidth, config->WindowHeight);
#endif

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