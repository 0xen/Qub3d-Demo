#include <qub3d\BUILD_ORDER.hpp>

VulkanPhysicalDevice::VulkanPhysicalDevice()
{
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

VkPhysicalDevice* VulkanPhysicalDevice::getSuitablePhysicalDevice(VkInstance& instance)
{
	return nullptr;
}

std::vector<VkPhysicalDevice> VulkanPhysicalDevice::GetPhysicalDevices(VkInstance & instance)
{
	uint32_t device_count = 0;
	std::vector<VkPhysicalDevice> devices;
	bool error = VulkanInitializers::validate(vkEnumeratePhysicalDevices(
		instance,
		&device_count,
		nullptr
	));
	devices.resize(device_count);

	if(error) return devices;

	error = VulkanInitializers::validate(vkEnumeratePhysicalDevices(
		instance,
		&device_count,
		devices.data()
	));
	return devices;
}
