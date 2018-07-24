#include <viking/vulkan/VulkanInitializers.hpp>

using namespace viking::vulkan;

bool VulkanInitializers::validate(VkResult result)
{
    return result == VK_SUCCESS;
}

VkApplicationInfo VulkanInitializers::applicationInfo(const char * app_name, uint32_t app_ver, const char * engine_name, uint32_t engine_ver, uint32_t api_version)
{
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = app_name;
    app_info.applicationVersion = app_ver;
    app_info.pEngineName = engine_name;
    app_info.engineVersion = engine_ver;
    app_info.apiVersion = api_version;
    return app_info;
}

VkInstanceCreateInfo VulkanInitializers::instanceCreateInfo(VkApplicationInfo & app_info, std::vector<const char*>& instance_extensions, std::vector<const char*>& instance_layers)
{
    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = (uint32_t)instance_extensions.size();
    create_info.ppEnabledExtensionNames = instance_extensions.data();
    create_info.enabledLayerCount = (uint32_t)instance_layers.size();
    create_info.ppEnabledLayerNames = instance_layers.data();
    return create_info;
}

VkDeviceCreateInfo viking::vulkan::VulkanInitializers::deviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queue_create_infos, const std::vector<const char*>& device_extensions, VkPhysicalDeviceFeatures & device_features)
{
	VkDeviceCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	create_info.pQueueCreateInfos = queue_create_infos.data();
	create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
	create_info.pEnabledFeatures = &device_features;
	create_info.enabledExtensionCount = (uint32_t)device_extensions.size();
	create_info.ppEnabledExtensionNames = device_extensions.data();
	return create_info;
}

VkCommandPoolCreateInfo viking::vulkan::VulkanInitializers::commandPoolCreateInfo(uint32_t queue_family_index, VkCommandPoolCreateFlags flags)
{
	VkCommandPoolCreateInfo pool_info = {};
	pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pool_info.queueFamilyIndex = queue_family_index;
	pool_info.flags = flags;
	return pool_info;
}

VkDeviceQueueCreateInfo viking::vulkan::VulkanInitializers::deviceQueueCreate(uint32_t queue_family_index, float queue_priority)
{
	VkDeviceQueueCreateInfo queue_create_info = {};
	queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueFamilyIndex = queue_family_index;
	queue_create_info.queueCount = 1;
	queue_create_info.pQueuePriorities = &queue_priority;
	return queue_create_info;
}
