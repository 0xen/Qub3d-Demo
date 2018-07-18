#include <qub3d\BUILD_ORDER.hpp>

VulkanWindow::VulkanWindow(const char *title, int w, int h)
{
    m_window = SDL_CreateWindow(
        "Qub3d Demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w,
        h,
        SDL_WINDOW_VULKAN);

    
    SDL_ShowWindow(m_window);
	m_running = true;
}