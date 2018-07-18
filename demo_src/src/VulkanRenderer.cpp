#include <qub3d\BUILD_ORDER.hpp>

VulkanRenderer::VulkanRenderer()
{
	SetupVulkan();
}

VulkanRenderer::~VulkanRenderer()
{
	delete m_instance;
}

void VulkanRenderer::render()
{
}

void VulkanRenderer::SetupVulkan()
{
	m_instance = new VulkanInstance();
}
