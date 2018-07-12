#include <qub3d/window.hpp>

int main(int argc, char **argv)
{
    int width = 640;
    int height = 480;

    Window window("Qub3d", width, height);
    window.pollEvents();

    while (window.isRunning())
    {                
        window.pollEvents();

        window.sleep(1000 / 60.f);
    }

    return 0;
}