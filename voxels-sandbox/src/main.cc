#include <qub3d/q3shared_constants.hpp>
#include <qub3d/q3window.hpp>
#include <qub3d/q3renderer.hpp>
#include <qub3d/q3camera.hpp>
#include <qub3d/q3perlin.hpp>
#include <qub3d/q3world.hpp>
#undef main

#include <time.h>
#include <iostream>

int main(int argc, char **argv)
{
    srand(static_cast<unsigned int>(time(NULL)));
    SDL_Init(SDL_INIT_EVERYTHING);

    Q3Window window(Q3_WINDOWTITLE, Q3_WINDOWWIDTH, Q3_WINDOWHEIGHT);
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