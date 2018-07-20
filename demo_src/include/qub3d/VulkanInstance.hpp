#pragma once

#include <vector>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <qub3d\VulkanInitializers.hpp>

class VulkanInstance
{
public:
    VulkanInstance();
    ~VulkanInstance();
    VkInstance& getInstance();
    void start();
    void addExtenstion(const char* extension);
private:
    void setupLayersAndExtensions();
    void initVulkanInstance();
    void deInitVulkanInstance();
    std::vector<const char*> instance_extensions;
    std::vector<const char*> instance_layers;
    VkInstance m_instance;
};