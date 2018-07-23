#pragma once

#include <viking/IWindow.hpp>
#include <viking/API.hpp>

namespace viking 
{
	class IRenderer
	{
	public:

		static IRenderer* createRenderer(IWindow* window,const RenderingAPI& api);
	private:
	};
}