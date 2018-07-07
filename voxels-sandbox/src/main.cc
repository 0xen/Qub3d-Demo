#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#undef main

#include <qub3d/shared_constants.hpp>
#include <qub3d/q3window.hpp>
#include <qub3d/q3renderer.hpp>
#include <qub3d/q3camera.hpp>
#include <qub3d/q3perlin.hpp>

#include <time.h>
#include <math.h>

#define ROUNDF(f, c) (((float)((int)((f) * (c))) / (c)))

struct Q3Cube {
    glm::vec3 position;
    glm::vec3 color;
};

float mapRange(float input, float input_start, float input_end, float output_start, float output_end) {
    float slope = 1.f * (output_end - output_start) / (input_end - input_start);
    return output_start + slope * (input - input_start);
}

int main(int argc, char **argv) {
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    
    Q3Window window(Q3_WINDOWTITLE, Q3_WINDOWWIDTH, Q3_WINDOWHEIGHT);
    window.pollEvents();

    Q3Camera camera(window.getWindow());
    Q3Renderer renderer;
    Q3PerlinNoiseGenerator perlin_noise_generator;
    
    const int mapsize = 50;
    Q3Cube terrain[mapsize * mapsize];
    for (int z = 0; z < mapsize; ++z) {
        for (int x = 0; x < mapsize; ++x) {
            Q3Cube& r = terrain[x + z * mapsize];
            r.position.x = x*2;
            float pNorm = perlin_noise_generator.perlin(glm::vec3((x*2) / 10.f, (z*2) / 10.0f, 0.f));
            r.position.y = pNorm*20;
            r.position.z = z*2;
            r.color = glm::vec3(126.f / 255.f, 214.f / 255.f, 145.f / 255.f);
        }
    }

    glm::vec3 red(1.0f, 0.0f, 0.0f);
    glm::vec3 blue(0.0f, 0.0f, 1.0f);

    float last = SDL_GetTicks();
    while (window.isRunning()) {
        float current = SDL_GetTicks();

        float dt = current - last;
        window.pollEvents();

        camera.update(dt);
        renderer.clear();
        
        renderer.handleCamera(&camera);
        for (int i = 0; i < mapsize * mapsize; ++i) {
            Q3Cube p = terrain[i];
            renderer.drawCube(p.position.x, p.position.y, p.position.z, 1, 1, 1, p.color);
        }
        /*renderer.drawCube(0, 0, 0, 1, 1, 1, red);
        renderer.drawCube(2, 0, 0, 1, 1, 1, blue);
        renderer.drawCube(0, 0, 2, 1, 1, 1, blue);
        renderer.drawCube(2, 0, 2, 1, 1, 1, red);
        */
        window.swapBuffers();

        last = current;
        window.sleep(1000 / 60.f);
    }

    return 0;
}