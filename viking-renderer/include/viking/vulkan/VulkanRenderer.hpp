#pragma once

#include <vulkan/vulkan.h>

#include <viking/vulkan/VulkanInstance.hpp>
#include <viking/vulkan/VulkanPhysicalDevice.hpp>
#include <viking/vulkan/VulkanWindow.hpp>
#include <viking/vulkan/IVulkanSurface.hpp>

#include <viking/IRenderer.hpp>

namespace viking { namespace vulkan
{
    class VulkanRenderer : public IRenderer
    {
    public:
        VulkanRenderer();
        ~VulkanRenderer();
        virtual void render();
		virtual void start();
    private:
        void setupVulkan();
        VulkanInstance * m_instance;
		VulkanWindow* m_vulkan_window;
		IVulkanSurface* m_vulkan_surface;
        VulkanPhysicalDevice* m_pdevice;
    };
}}