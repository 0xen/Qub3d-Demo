#pragma once

#include <viking/API.hpp>
#include <viking/IRenderingSurface.hpp>

namespace viking 
{
	class IRenderer
	{
	public:
        IRenderingSurface * createSurface();

		static IRenderer* createRenderer(const RenderingAPI& api);
	private:
	};
}