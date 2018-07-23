#include <viking/vulkan/VulkanRenderer.hpp>
#include <viking/vulkan/VulkanSDLWindow.hpp>
#include <viking/IWindow.hpp>

using namespace viking;
using namespace viking::vulkan;

VulkanRenderer::VulkanRenderer(IWindow* window)
{
	switch (window->GetWindowingAPI())
	{
	case WindowingAPI::SDL:
		m_window = static_cast<vulkan::VulkanSDLWindow*>(window);
		break;
	}
    setupVulkan();
}

VulkanRenderer::~VulkanRenderer()
{
    //delete m_pdevice;
    delete m_instance;
}

void VulkanRenderer::render()
{
}

void VulkanRenderer::setupVulkan()
{
    m_instance = new VulkanInstance();

    const char** extentions = NULL;
    unsigned int count = 0;
    // Get the total count of all required extentions
	count = m_window->getExtensionsCount();

    // Add them to the instance
    for (unsigned int i = 0; i < count; i++)
    {
        m_instance->addExtenstion(m_window->getExtensions()[i]);
    }

    m_instance->start();
    /*m_window->initilizeSurface(m_instance->getInstance());
    m_pdevice = VulkanPhysicalDevice::getSuitablePhysicalDevice(m_instance->getInstance(), m_window->getSurface());*/
}
