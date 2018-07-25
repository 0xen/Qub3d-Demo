#pragma once

#include <vulkan/vulkan.h>

#include <set>
#include <vector>

#include <viking/vulkan/VulkanInitializers.hpp>
#include <viking/vulkan/VulkanQueueFamilyIndices.hpp>

namespace viking { namespace vulkan {

    class VulkanPhysicalDevice
    {
    public:
        VulkanPhysicalDevice(VkPhysicalDevice device, VulkanQueueFamilyIndices queue_family);
        ~VulkanPhysicalDevice();

		VkPhysicalDevice& GetPhysicalDevice();
		VulkanQueueFamilyIndices * getQueueFamilies();
		std::vector<const char*>& GetExtenstions();
		VkPhysicalDeviceFeatures& GetDeviceFeatures();
		VkPhysicalDeviceMemoryProperties* getPhysicalDeviceMemoryProperties();


        static VulkanPhysicalDevice* getSuitablePhysicalDevice(VkInstance& instance, VkSurfaceKHR& surface);
        static std::vector<VkPhysicalDevice> getPhysicalDevices(VkInstance& instance);
        static bool checkDeviceExtensionSupport(VkPhysicalDevice& device);
        static bool supportsQueueFamily(VkPhysicalDevice & device, VulkanQueueFamilyIndices & queue_family_indices, VkSurfaceKHR& surface);

    private:
        std::vector<const char*> m_device_extensions;

        VkPhysicalDevice m_device;
        VulkanQueueFamilyIndices m_queue_family;
        VkPhysicalDeviceProperties m_physical_device_properties;
        VkPhysicalDeviceFeatures m_device_features;
        VkPhysicalDeviceMemoryProperties m_physical_device_mem_properties;
    };
}}