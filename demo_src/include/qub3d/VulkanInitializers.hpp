#pragma once

#include <qub3d\BUILD_ORDER.hpp>

namespace VulkanInitializers
{
	bool validate(VkResult result);

	VkApplicationInfo applicationInfo(const char* app_name, uint32_t app_ver, const char* engine_name, uint32_t engine_ver, uint32_t api_version);

	VkInstanceCreateInfo instanceCreateInfo(VkApplicationInfo & app_info, std::vector<const char*>& instance_extensions, std::vector<const char*>& instance_layers);
}