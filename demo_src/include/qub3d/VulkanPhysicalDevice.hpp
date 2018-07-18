#pragma once

#include <qub3d\BUILD_ORDER.hpp>

class VulkanPhysicalDevice
{
public:
	VulkanPhysicalDevice();
	~VulkanPhysicalDevice();
	static VkPhysicalDevice* getSuitablePhysicalDevice(VkInstance& instance);
	static std::vector<VkPhysicalDevice> GetPhysicalDevices(VkInstance& instance);
};