#include <qub3d\VulkanInitializers.hpp>

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
