#include <viking/SDLWindowProvider.hpp>

using namespace viking;

SDL_Window *SDLWindowProvider::createWindow(const WindowDescriptor& windowInfo, const API& api)
{
    switch (api)
    {
    case API::Vulkan:
        return SDL_CreateWindow(
            windowInfo.title, 
            windowInfo.windowposX, windowInfo.windowposY, 
            windowInfo.width, windowInfo.height, 
            SDL_WINDOW_VULKAN
        );
    case API::GL11: // Window setup for GL11 and GL3 are the same so we can just fallthrough here
    case API::GL3:
        return SDL_CreateWindow(
            windowInfo.title,
            windowInfo.windowposX, windowInfo.windowposY,
            windowInfo.width, windowInfo.height,
            SDL_WINDOW_OPENGL
        );
    }
}