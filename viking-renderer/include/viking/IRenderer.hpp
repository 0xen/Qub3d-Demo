#pragma once

#include <viking/API.hpp>
#include <viking/IRenderingSurface.hpp>

namespace viking 
{
	class IRenderer
	{
	public:
        IRenderingSurface * createSurface();

	private:
	};

    class Renderer
    {
    public:
		static IRenderer* createRenderer(const API& api);
    };
}