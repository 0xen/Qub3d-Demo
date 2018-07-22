#pragma once

#include <vulkan/vulkan.h>

#include <viking/vulkan/VulkanInstance.hpp>
#include <viking/vulkan/VulkanRenderer.hpp>
#include <viking/vulkan/VulkanPhysicalDevice.hpp>

#include <viking/IRenderer.hpp>

namespace viking { namespace vulkan
{
    class VulkanRenderer /*: public IRenderer*/
    {
    public:
   //     VulkanRenderer(IWindow* window);
        ~VulkanRenderer();
        virtual void render();
    private:
        void setupVulkan();
        VulkanInstance * m_instance;
//        VulkanWindow* m_window;
        VulkanPhysicalDevice* m_pdevice;
    };
}}