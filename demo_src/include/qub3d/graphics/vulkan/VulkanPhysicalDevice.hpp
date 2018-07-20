#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <set>
#include <vector>
#include <qub3d\VulkanInitializers.hpp>

struct QueueFamilyIndices
{
    uint32_t graphics_indices = UINT32_MAX;
    uint32_t present_indices = UINT32_MAX;
    uint32_t compute_indices = UINT32_MAX;
    bool isComplete()
    {
        return graphics_indices < UINT32_MAX &&
            present_indices < UINT32_MAX &&
            compute_indices < UINT32_MAX;
    }
    void clear()
    {
        graphics_indices = UINT32_MAX;
        present_indices = UINT32_MAX;
        compute_indices = UINT32_MAX;
    }
};

class VulkanPhysicalDevice
{
public:
    VulkanPhysicalDevice(VkPhysicalDevice device, QueueFamilyIndices queue_family);
    ~VulkanPhysicalDevice();
    static VulkanPhysicalDevice* getSuitablePhysicalDevice(VkInstance& instance, VkSurfaceKHR& surface);
    static std::vector<VkPhysicalDevice> getPhysicalDevices(VkInstance& instance);
    static bool checkDeviceExtensionSupport(VkPhysicalDevice& device);
    static bool supportsQueueFamily(VkPhysicalDevice & device, QueueFamilyIndices & queue_family_indices, VkSurfaceKHR& surface);

private:

    std::vector<const char*> device_extensions;
    VkPhysicalDevice m_device;
    QueueFamilyIndices m_queue_family;
    VkPhysicalDeviceProperties m_physical_device_properties;
    VkPhysicalDeviceFeatures m_device_features;
    VkPhysicalDeviceMemoryProperties m_physical_device_mem_properties;
};