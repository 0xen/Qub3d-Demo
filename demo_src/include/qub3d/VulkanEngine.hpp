#pragma once

#include <qub3d/IRenderer.hpp>

class VulkanEngine : public IEngine
{
public:
	VulkanEngine();
	bool Start();
	void Stop();
	void Render();
	void Update();
};