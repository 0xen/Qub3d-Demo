#pragma once

#include <viking/WindowDescriptor.hpp>
#include <viking/SDLWindow.hpp>

namespace viking
{
	class VulkanSDLWindow : public SDLWindow
	{
	public:
		VulkanSDLWindow(WindowDescriptor descriptor);
	};
}