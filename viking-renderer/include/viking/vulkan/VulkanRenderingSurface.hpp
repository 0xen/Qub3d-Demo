#pragma once

#include <viking/IRenderingSurface.hpp>

#include <vulkan/vulkan.h>

namespace viking { namespace vulkan {
    class VulkanRenderingSurface : public IRenderingSurface
    {
    public:
        VulkanRenderingSurface(SDL_Window* window) : IRenderingSurface(window) {}
        
        virtual void create();

    private:
        VkSurfaceKHR m_surface;
        
        void getExtensions(const char **extensions, size_t count);
        void getExtensionsCount(size_t count);
    };
}}