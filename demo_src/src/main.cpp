#include <qub3d/window.hpp>
#include <qub3d/settings.hpp>

#include <nlohmann/json.hpp>
#include <fstream>

int main(int argc, char **argv)
{
    Settings::GameConfig *configurations = Settings::GameConfig::Get();
    configurations->LoadFromFile("assets/config.json");

    Window window("Qub3d", configurations->WindowWidth, configurations->WindowHeight);
    
    while (window.isRunning())
    {
        window.pollEvents();
        window.swapBuffers();
        window.sleep(1000 / 60.f);
    }

    return 0;
}