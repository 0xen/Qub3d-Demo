#include <viking/vulkan/VulkanWindow.hpp>

using namespace viking::vulkan;

VulkanWindow::VulkanWindow()
{

}

VulkanWindow::~VulkanWindow()
{

}

const char** VulkanWindow::getExtensions()
{
	return m_extentions;
}

unsigned int VulkanWindow::getExtensionsCount()
{
	return m_extension_count;
}
