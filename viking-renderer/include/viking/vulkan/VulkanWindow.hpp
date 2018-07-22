#pragma once

#include <cassert>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <qub3d\VulkanInstance.hpp>
#include <qub3d\IWindow.hpp>
#include <SDL_vulkan.h>


class VulkanWindow : public IWindow
{
public:
    VulkanWindow(const char *title, int w, int h);
    void initilizeSurface(VkInstance& instance);
    VkSurfaceKHR& getSurface();
    void getExtensions(const char** extentions, unsigned int& count);
    void getExtensionsCount(unsigned int& count);
private:
    VkSurfaceKHR m_surface;
};