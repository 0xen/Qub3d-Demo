#include <viking/vulkan/VulkanPhysicalDevice.hpp>

using namespace viking::vulkan;

VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice device, QueueFamilyIndices queue_family)
{
    m_device = device;
    m_queue_family = queue_family;

    vkGetPhysicalDeviceProperties(
        device,
        &m_physical_device_properties
    );


    // Get the devices physical features
    vkGetPhysicalDeviceFeatures(
        device,
        &m_device_features
    );
    // Get the GPU's memory props
    vkGetPhysicalDeviceMemoryProperties(
        device,
        &m_physical_device_mem_properties
    );

    device_extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
    // Dose not need clean up
}

VulkanPhysicalDevice* VulkanPhysicalDevice::getSuitablePhysicalDevice(VkInstance& instance, VkSurfaceKHR& surface)
{
    VulkanPhysicalDevice* responce = VK_NULL_HANDLE;
    std::vector<VkPhysicalDevice> devices = getPhysicalDevices(instance);

    VkPhysicalDevice chosen_device = VK_NULL_HANDLE;
    QueueFamilyIndices chosen_queue_family;
    for (auto& device : devices)
    {
        QueueFamilyIndices queue_family;
        if (checkDeviceExtensionSupport(device) && supportsQueueFamily(device, queue_family, surface ))
        {
            VkPhysicalDeviceProperties temp_physical_device_properties;
            vkGetPhysicalDeviceProperties(
                device,
                &temp_physical_device_properties
            );
            // Select the first GPU if its okay
            if (chosen_device == VK_NULL_HANDLE || chosen_device != VK_NULL_HANDLE && temp_physical_device_properties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
                chosen_device = device;
                chosen_queue_family = queue_family;
            }
        }

        
    }
    responce = new VulkanPhysicalDevice(chosen_device, chosen_queue_family);
    return responce;
}


std::vector<VkPhysicalDevice> VulkanPhysicalDevice::getPhysicalDevices(VkInstance & instance)
{
    uint32_t device_count = 0;
    std::vector<VkPhysicalDevice> devices;
    bool wasSuccsess = VulkanInitializers::validate(vkEnumeratePhysicalDevices(
        instance,
        &device_count,
        nullptr
    ));
    devices.resize(device_count);

    if(!wasSuccsess) return devices;

    wasSuccsess = VulkanInitializers::validate(vkEnumeratePhysicalDevices(
        instance,
        &device_count,
        devices.data()
    ));
    return devices;
}

bool VulkanPhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice & device)
{
    uint32_t extension_count;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);
    std::vector<VkExtensionProperties> available_extensions(extension_count);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());
    std::vector<const char*> device_extensions{
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    std::set<std::string> required_extensions(device_extensions.begin(), device_extensions.end());
    // Loop through extensions and check 
    for (const auto& extension : available_extensions)
    {
        required_extensions.erase(extension.extensionName);
    }
    // If any extensions are left over, it failed
    return required_extensions.empty();
}

bool VulkanPhysicalDevice::supportsQueueFamily(VkPhysicalDevice & device, QueueFamilyIndices & queue_family_indices, VkSurfaceKHR& surface)
{
    uint32_t queue_family_count = 0;
    // Get the total amount of queue family's
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);
    // Get the queue families
    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

    uint32_t i = 0;
    for (const auto& queue_family : queue_families)
    {
        if (queue_family.queueCount > 0)
        {
            queue_family_indices.clear();
            if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                queue_family_indices.graphics_indices = i;
            if (queue_family.queueFlags & VK_QUEUE_COMPUTE_BIT)
                queue_family_indices.compute_indices = i;

            VkBool32 present_support = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(
                device,
                i,
                surface,
                &present_support
            );
            if (present_support)
                queue_family_indices.present_indices = i;

            if (queue_family_indices.isComplete()) return true;
        }
        i++;
    }
    return false;
}
