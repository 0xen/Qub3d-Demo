#pragma once

#include <SDL.h>

namespace viking
{
	struct WindowDescriptor
	{
		int width, height;
		int windowposX, windowposY;

		const char *title;

		WindowDescriptor(const char* title, int w, int h, int windowposX = SDL_WINDOWPOS_CENTERED, int windowposY = SDL_WINDOWPOS_CENTERED) :
			title(title), width(w), height(h), windowposX(windowposX), windowposY(windowposY)
		{
		}
	};
}