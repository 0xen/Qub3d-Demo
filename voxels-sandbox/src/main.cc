#include <qub3d/q3shared_constants.hpp>
#include <qub3d/q3window.hpp>
#include <qub3d/q3renderer.hpp>
#include <qub3d/q3camera.hpp>
#include <qub3d/q3perlin.hpp>
#undef main

#include <time.h>

struct Q3Cube
{
    glm::vec3 position;
    glm::vec3 color;
};

int main(int argc, char **argv)
{
    srand(static_cast<unsigned int>(time(NULL)));
    SDL_Init(SDL_INIT_EVERYTHING);

    Q3Window window(Q3_WINDOWTITLE, Q3_WINDOWWIDTH, Q3_WINDOWHEIGHT);
    window.pollEvents();

    Q3Camera camera(window.getWindow());
    Q3Renderer renderer;
    Q3PerlinNoiseGenerator perlin_noise_generator;

    const int mapsize = 50;
    Q3Cube terrain[mapsize * mapsize];
    for (int z = 0; z < mapsize; ++z)
    {
        for (int x = 0; x < mapsize; ++x)
        {
            Q3Cube &r = terrain[x + z * mapsize];
            r.position.x = x * 2.f;
            float pNorm = perlin_noise_generator.perlin(glm::vec3((x * 2) / 10.f, (z * 2) / 10.0f, 0.f));
            r.position.y = pNorm * 15.f;
            r.position.z = z * 2.f;
            r.color = glm::vec3(127.f / 255.f, 214.f / 255.f, 145.f / 255.f);
        }
    }

    Uint32 last_time = SDL_GetTicks();
    while (window.isRunning())
    {
        Uint32 current_time = SDL_GetTicks();

        float dt = static_cast<float>(current_time - last_time);
        window.pollEvents();

        camera.update(dt);
        renderer.clear();

        renderer.handleCamera(&camera);
        for (int i = 0; i < mapsize * mapsize; ++i)
        {
            Q3Cube p = terrain[i];

            p.position.x = std::round(+p.position.x);
            p.position.y = std::round(+p.position.y);
            p.position.z = std::round(+p.position.z);

            renderer.drawCube(p.position.x, p.position.y, p.position.z, 1, 1, 1, p.color);
        }

        window.swapBuffers();

        last_time = current_time;
        window.sleep(1000 / 60.f);
    }

    return 0;
}