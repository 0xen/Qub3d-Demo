#pragma once

#include <vulkan/vulkan.h>

#include <set>
#include <vector>

#include <viking/vulkan/VulkanInitializers.hpp>
#include <viking/vulkan/VulkanPhysicalDevice.hpp>

namespace viking { namespace vulkan {

    class VulkanDevice
    {
    public:
		VulkanDevice(VulkanPhysicalDevice* physical_device);
		~VulkanDevice();
		VkDevice& GetVulkanDevice();
		VulkanPhysicalDevice& GetPhysicalDevice();
		VkQueue* GetGraphicsQueue();
		VkQueue* GetPresentQueue();
		VkQueue* GetComputeQueue();
		VkCommandPool* GetGraphicsCommandPool();
		VkCommandPool* GetComputeCommandPool();
    private:
		VkDevice m_device = VK_NULL_HANDLE;
		VkQueue m_graphics_queue;
		VkQueue m_present_queue;
		VkQueue m_compute_queue;
		VkCommandPool m_graphics_command_pool;
		VkCommandPool m_compute_command_pool;
		VulkanPhysicalDevice* m_physical_device;
    };
}}