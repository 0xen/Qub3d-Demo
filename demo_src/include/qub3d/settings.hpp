#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace settings
{

const int DEFAULTWINDOWWIDTH = 1280;
const int DEFAULTWINDOWHEIGHT = 720;

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
};

} // namespace settings