#pragma once

#include <qub3d\BUILD_ORDER.hpp>

class VulkanInstance
{
public:
	VulkanInstance();
	~VulkanInstance();
private:
	void setupLayersAndExtensions();
	void initVulkanInstance();
	void deInitVulkanInstance();
	std::vector<const char*> instance_extensions;
	std::vector<const char*> instance_layers;
	VkInstance m_instance;
};