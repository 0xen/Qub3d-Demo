#include <qub3d\VulkanWindow.hpp>

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

void VulkanWindow::initilizeSurface(VkInstance & instance)
{
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    assert(SDL_GetWindowWMInfo(m_window, &info) == SDL_TRUE);

    VkWin32SurfaceCreateInfoKHR w32sci = {};
    w32sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    w32sci.pNext = NULL;
    w32sci.hinstance = GetModuleHandle(NULL);
    w32sci.hwnd = info.info.win.window;

    vkCreateWin32SurfaceKHR(
        instance,
        &w32sci,
        nullptr,
        &m_surface);

}

VkSurfaceKHR & VulkanWindow::getSurface()
{
    return m_surface;
}

void VulkanWindow::getExtensions(const char ** extentions, unsigned int & count)
{
    SDL_Vulkan_GetInstanceExtensions(m_window, &count, extentions);
}

void VulkanWindow::getExtensionsCount(unsigned int & count)
{
    SDL_Vulkan_GetInstanceExtensions(m_window, &count, NULL);
}
