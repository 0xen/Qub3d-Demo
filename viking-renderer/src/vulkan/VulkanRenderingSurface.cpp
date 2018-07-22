#include <viking/vulkan/VulkanRenderingSurface.hpp>

#include <SDL_vulkan.h>

using namespace viking::vulkan;

void VulkanRenderingSurface::create()
{

}

void VulkanRenderingSurface::getExtensions(const char** extensions, size_t count)
{
    SDL_Vulkan_GetInstanceExtensions(m_window, &count, extensions);
}

void VulkanRenderingSurface::getExtensionsCount(size_t count)
{
    SDL_Vulkan_GetInstanceExtensions(m_window, &count, nullptr);
}
