#include <viking/SDLWindowProvider.hpp>
#include <viking/IRenderingSurface.hpp>
#include <viking/IRenderer.hpp>

int main(int argc, char **argv) {
    using namespace viking;

    const API api = API::Vulkan;

    SDL_Window *window = SDLWindowProvider::createWindow(WindowDescriptor("Qub3d Demo", 800, 600), api);

    IRenderer *renderer = Renderer::createRenderer(api);
    

    return 0;
}
