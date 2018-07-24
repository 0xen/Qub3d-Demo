#pragma once
#include <assert.h>
#include <viking/WindowDescriptor.hpp>
#include <viking/vulkan/VulkanWindow.hpp>
#include <viking/vulkan/VulkanSDLSurface.hpp>
#include <viking/SDLWindow.hpp>

namespace viking {
	namespace vulkan {
		class VulkanSDLWindow : public SDLWindow, public VulkanSDLSurface, public VulkanWindow
		{
		public:
			VulkanSDLWindow(WindowDescriptor descriptor);
		private:
		};
	}
}