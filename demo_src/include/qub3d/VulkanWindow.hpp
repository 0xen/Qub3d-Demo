#pragma once

#include <qub3d\BUILD_ORDER.hpp>

class VulkanWindow : public IWindow
{
public:
	VulkanWindow(const char *title, int w, int h);
};