#pragma once

#include <vector>
#include <vulkan/vulkan.hpp>

#include <viking/vulkan/VulkanInstance.hpp>

namespace viking { namespace vulkan {
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
}}