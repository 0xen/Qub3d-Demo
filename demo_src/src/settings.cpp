#include <qub3d/settings.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

void Settings::GameConfig::LoadFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    std::string configFileText(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    nlohmann::json configFile = nlohmann::json::parse(configFileText);
        
    WindowWidth = configFile["display"]["width"];
    WindowHeight = configFile["display"]["height"];
}