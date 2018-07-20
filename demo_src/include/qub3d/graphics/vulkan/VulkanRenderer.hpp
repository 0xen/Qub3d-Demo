#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <qub3d\VulkanInstance.hpp>
#include <qub3d\IRenderer.hpp>
#include <qub3d\VulkanWindow.hpp>
#include <qub3d\VulkanPhysicalDevice.hpp>

class VulkanRenderer : public IRenderer
{
public:
    VulkanRenderer(IWindow* window);
    ~VulkanRenderer();
    virtual void render();
private:
    void setupVulkan();
    VulkanInstance * m_instance;
    VulkanWindow* m_window;
    VulkanPhysicalDevice* m_pdevice;
};
