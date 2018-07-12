#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Settings
{
    public:
        const int DEFAULTWINDOWWIDTH = 1280;
        const int DEFAULTWINDOWHEIGHT 720;

        const std::string WINDOWTITLE = "Qub3d Demo";
        const std::string WINDOWTITLE_PAUSED = "Qub3d Demo - Paused";

        struct GameConfig
        {
            int WindowWidth = DEFAULTWINDOWWIDTH
            int WindowHeight = DEFAULTWINDOWHEIGHT

            static GameConfig *Get()
            {
                static GameConfig config;
                return &config;
            }
        }
}