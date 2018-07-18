#include <qub3d\BUILD_ORDER.hpp>

VulkanInstance::VulkanInstance()
{
	initVulkanInstance();
}

VulkanInstance::~VulkanInstance()
{
	deInitVulkanInstance();
}

void VulkanInstance::setupLayersAndExtensions()
{
	instance_extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
}

void VulkanInstance::initVulkanInstance()
{
	VkApplicationInfo app_info = VulkanInitializers::applicationInfo(
		"Qub3d",
		VK_MAKE_VERSION(1, 0, 0),
		"Qub3d",
		VK_MAKE_VERSION(1, 0, 0),
		VK_MAKE_VERSION(1, 0, 68)
	);
	VkInstanceCreateInfo create_info = VulkanInitializers::instanceCreateInfo(
		app_info,
		instance_extensions,
		instance_layers
	);
	// Need to handle with I/O
	bool sucsess = VulkanInitializers::validate(vkCreateInstance(
		&create_info,
		NULL,
		&m_instance
	));
}

void VulkanInstance::deInitVulkanInstance()
{
	vkDestroyInstance(
		m_instance,
		NULL
	);
}
