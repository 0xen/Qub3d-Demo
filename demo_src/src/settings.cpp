#include <qub3d\BUILD_ORDER.hpp>

void Settings::GameConfig::loadFromFile(const std::string& filename)
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