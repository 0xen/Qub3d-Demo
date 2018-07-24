#pragma once

#include <viking/IWindow.hpp>
#include <viking/API.hpp>

namespace viking 
{
	class IRenderer
	{
	public:

		static IRenderer* createRenderer(const RenderingAPI& api);
		void addWindow(IWindow* window);
		virtual void start() = 0;
		virtual void render() = 0;
	protected:
		// Just storing a single window for now
		IWindow * m_window;
	};
}