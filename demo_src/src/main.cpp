#include <qub3d/window.hpp>
#include <qub3d/settings.hpp>

#include <nlohmann/json.hpp>
#include <fstream>

int main(int argc, char **argv)
{
    // Get configurations
    using json = nlohmann::json;
    std::ifstream file("assets/config.json"); 
    std::string str((std::istreambuf_iterator<char>(file)),
    std::istreambuf_iterator<char>());
    json config_file = json::parse(str);

    Settings::GameConfig *configurations = Settings::GameConfig::Get();
    configurations->WindowWidth = config_file["display"]["width"];
    configurations->WindowHeight = config_file["display"]["height"];


    Window window("Qub3d", configurations->WindowWidth, configurations->WindowHeight);
    window.pollEvents();

    while (window.isRunning())
    {
        window.pollEvents();
        window.swapBuffers();
        window.sleep(1000 / 60.f);
    }

    return 0;
}