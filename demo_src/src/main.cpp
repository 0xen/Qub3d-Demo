#include <qub3d/window.hpp>
#include <qub3d/settings.hpp>

int main(int argc, char **argv)
{
    // Get configurations and initialise variables
    GameConfig *settings = CameConfig::Get();
    
    settings = CameConfig::AutoSet();

    Window window("Qub3d", settings->WindowWidth, settings->WindowHeight);
    window.pollEvents();

    while (window.isRunning())
    {                
        window.pollEvents();

        window.sleep(1000 / 60.f);
    }

    return 0;
}