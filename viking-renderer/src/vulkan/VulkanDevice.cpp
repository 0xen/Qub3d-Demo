#include <viking/vulkan/VulkanDevice.hpp>

using namespace viking::vulkan;

VulkanDevice::VulkanDevice(VulkanPhysicalDevice* physical_device)
{
	m_physical_device = physical_device;
	std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
	std::vector<uint32_t> unique_queue_families;
	unique_queue_families.push_back(physical_device->getQueueFamilies()->graphics_indices);
	unique_queue_families.push_back(physical_device->getQueueFamilies()->compute_indices);

	for (auto queue_family : unique_queue_families)
	{
		queue_create_infos.push_back(VulkanInitializers::deviceQueueCreate(queue_family, 1.0f));
	}


	VkDeviceCreateInfo create_info = VulkanInitializers::deviceCreateInfo(
		queue_create_infos,
		physical_device->GetExtenstions(),
		physical_device->GetDeviceFeatures()
	);

	bool sucsess = VulkanInitializers::validate(vkCreateDevice(
		physical_device->GetPhysicalDevice(),
		&create_info,
		nullptr,
		&m_device
	));

	vkGetDeviceQueue(
		m_device,
		physical_device->getQueueFamilies()->compute_indices,
		0,
		&m_compute_queue
	);
	vkGetDeviceQueue(
		m_device,
		physical_device->getQueueFamilies()->graphics_indices,
		0,
		&m_graphics_queue
	);
	vkGetDeviceQueue(
		m_device,
		physical_device->getQueueFamilies()->graphics_indices,
		0,
		&m_present_queue
	);

	// Setup command pools
	VkCommandPoolCreateInfo compute_pool_info = VulkanInitializers::commandPoolCreateInfo(physical_device->getQueueFamilies()->compute_indices);
	sucsess = VulkanInitializers::validate(vkCreateCommandPool(
		m_device,
		&compute_pool_info,
		nullptr,
		&m_compute_command_pool
	));

	VkCommandPoolCreateInfo graphics_pool_info = VulkanInitializers::commandPoolCreateInfo(physical_device->getQueueFamilies()->graphics_indices);
	sucsess = VulkanInitializers::validate(vkCreateCommandPool(
		m_device,
		&graphics_pool_info,
		nullptr,
		&m_graphics_command_pool
	));



}

VulkanDevice::~VulkanDevice()
{
	vkDestroyCommandPool(
		m_device,
		m_graphics_command_pool,
		nullptr
	);

	vkDestroyCommandPool(
		m_device,
		m_compute_command_pool,
		nullptr
	);

	vkDestroyDevice(
		m_device,
		nullptr
	);
}

VkDevice& VulkanDevice::GetVulkanDevice()
{
	return m_device;
}

VulkanPhysicalDevice & viking::vulkan::VulkanDevice::GetPhysicalDevice()
{
	return *m_physical_device;
}

VkQueue * viking::vulkan::VulkanDevice::GetGraphicsQueue()
{
	return &m_graphics_queue;
}

VkQueue * viking::vulkan::VulkanDevice::GetPresentQueue()
{
	return &m_present_queue;
}

VkQueue * viking::vulkan::VulkanDevice::GetComputeQueue()
{
	return &m_compute_queue;
}

VkCommandPool * viking::vulkan::VulkanDevice::GetGraphicsCommandPool()
{
	return &m_graphics_command_pool;
}

VkCommandPool * viking::vulkan::VulkanDevice::GetComputeCommandPool()
{
	return &m_compute_command_pool;
}
