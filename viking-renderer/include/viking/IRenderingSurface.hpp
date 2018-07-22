#pragma once

#include <SDL.h>
#include <viking/API.hpp>

namespace viking
{
    class IRenderingSurface
    {
    protected:
        SDL_Window* m_window;

    public:
        IRenderingSurface(SDL_Window* window) : m_window(window) {}

        virtual void create() = 0;
    };
}