#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace settings
{

json *configurations
{
    using json = nlohmann::json;

    std::ifstream file("assets/config.json"); 
    std::string str((std::istreambuf_iterator<char>(file)),
    std::istreambuf_iterator<char>());
    configurations = json::parse(str);
}

int DEFAULTWINDOWWIDTH = configurations["display"]["width"];
int DEFAULTWINDOWHEIGHT = config_file["display"]["height"];

const std::string WINDOWTITLE = "Qub3d Demo"; // Title for SDL Window
const std::string WINDOWTITLE_PAUSED = "Qub3d Demo - Paused"; // Title for Paused SDL Window

struct GameConfig
{
    int WindowWidth = DEFAULTWINDOWWIDTH;
    int WindowHeight = DEFAULTWINDOWHEIGHT;

    static GameConfig *Get() // Function for getting the Config data.
    {
        static GameConfig config;
        return &config;
    }
    
    static GameConfig *AutoSet()
    {
        static GameConfig config;
        
        config->WindowWidth = configurations["display"]["width"];
        config->WindowHeight = configurations["display"]["height"];

        return &config
    }
};

} // namespace settings