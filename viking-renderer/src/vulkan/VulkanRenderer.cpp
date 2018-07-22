#include <viking/vulkan/VulkanRenderer.hpp>

using namespace viking::vulkan;
/*
VulkanRenderer::VulkanRenderer(IWindow* window)
{
    m_window = static_cast<VulkanWindow*>(window);
    setupVulkan();
}*/

VulkanRenderer::~VulkanRenderer()
{
    delete m_pdevice;
    delete m_instance;
}

void VulkanRenderer::render()
{
}

void VulkanRenderer::setupVulkan()
{
    /*m_instance = new VulkanInstance();

    const char** extentions = NULL;
    unsigned int count = 0;
    // Get the total count of all required extentions
    m_window->getExtensionsCount(count);
    extentions = new const char *[count];
    // Get the extentions names
    m_window->getExtensions(extentions,count);
    // Add them to the instance
    for (unsigned int i = 0; i < count; i++)
    {
        m_instance->addExtenstion(extentions[i]);
    }

    m_instance->start();
    m_window->initilizeSurface(m_instance->getInstance());
    m_pdevice = VulkanPhysicalDevice::getSuitablePhysicalDevice(m_instance->getInstance(), m_window->getSurface());*/
}
