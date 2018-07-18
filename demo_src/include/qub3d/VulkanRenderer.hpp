#pragma once
#include <qub3d\BUILD_ORDER.hpp>

class VulkanRenderer : public IRenderer
{
public:
	VulkanRenderer();
	~VulkanRenderer();
	virtual void render();
private:
	void SetupVulkan();
	VulkanInstance * m_instance;
};
