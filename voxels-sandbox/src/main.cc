#include <qub3d/q3shared_constants.hpp>
#include <qub3d/q3window.hpp>
#include <qub3d/q3renderer.hpp>
#include <qub3d/q3camera.hpp>
#include <qub3d/q3generator.hpp>
#include <qub3d/q3world.hpp>
#undef main

#include <time.h>
#include <iostream>

#include <nlohmann/json.hpp>
#include <fstream>

int main(int argc, char **argv)
{
    srand(static_cast<unsigned int>(time(NULL)));
    SDL_Init(SDL_INIT_EVERYTHING);

    Q3SharedConstants *constants = Q3SharedConstants::Get();

    using json = nlohmann::json;
    std::ifstream file("assets/config.json");
    std::string str((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    json config_file = json::parse(str);
    int window_width = config_file["display"]["width"];
    int window_height = config_file["display"]["height"];

    constants->WindowWidth = window_width; 
    constants->WindowHeight = window_height;

    Q3Window window(Q3_WINDOWTITLE, constants->WindowWidth, constants->WindowHeight);
    window.pollEvents();

    Q3Camera camera(window.getWindow());
    Q3Renderer renderer;
    
    Q3World world;
    world.generate();
    Q3WorldRenderer world_renderer;

    Uint32 last_time = SDL_GetTicks();
    while (window.isRunning())
    {
        Uint32 current_time = SDL_GetTicks();
        float dt = static_cast<float>(current_time - last_time);
        
        window.pollEvents();
        camera.update(dt);
        world.tick(&camera, &window);
        renderer.clear();
        renderer.start3d();
        {
            renderer.handleCamera(&camera);
            world_renderer.render(&world, &renderer);
        }
        renderer.end3d();

        renderer.start2d();
        {
            renderer.drawCrosshair();
        }
        renderer.end2d();

        window.swapBuffers();

        last_time = current_time;
        window.sleep(1000 / 60.f);
    }

    return 0;
}