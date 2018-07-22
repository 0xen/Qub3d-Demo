#pragma once

#include <viking/API.hpp>

namespace viking 
{
	class IRenderer
	{
	public:
		static IRenderer* createRenderer(const API& api);

	private:
	};
}