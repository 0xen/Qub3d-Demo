#pragma once

#include <viking/WindowDescriptor.hpp>
#include <viking/vulkan/VulkanWindow.hpp>
#include <viking/SDLWindow.hpp>

namespace viking {
	namespace vulkan {
		class VulkanSDLWindow : public SDLWindow, public VulkanWindow
		{
		public:
			VulkanSDLWindow(WindowDescriptor descriptor);
		};
	}
}