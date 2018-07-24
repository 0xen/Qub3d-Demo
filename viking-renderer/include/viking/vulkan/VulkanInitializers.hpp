#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace viking { namespace vulkan 
{
    struct VulkanInitializers
    {
        static bool validate(VkResult result);

        static VkApplicationInfo applicationInfo(const char* app_name, uint32_t app_ver, const char* engine_name, uint32_t engine_ver, uint32_t api_version);

        static VkInstanceCreateInfo instanceCreateInfo(VkApplicationInfo & app_info, std::vector<const char*>& instance_extensions, std::vector<const char*>& instance_layers);

		static VkDeviceQueueCreateInfo deviceQueueCreate(uint32_t queue_family_index, float queue_priority);

		static VkDeviceCreateInfo deviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queue_create_infos, const std::vector<const char*>& device_extensions, VkPhysicalDeviceFeatures& device_features);

		static VkCommandPoolCreateInfo commandPoolCreateInfo(uint32_t queue_family_index, VkCommandPoolCreateFlags flags = 0);


    };
}}