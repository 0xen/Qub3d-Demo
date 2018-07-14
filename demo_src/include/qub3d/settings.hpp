#pragma once
#include <string>

class Settings
{
    public:
        static const int DEFAULTWINDOWWIDTH = 1280;
        static const int DEFAULTWINDOWHEIGHT = 720;

        const std::string WINDOWTITLE = "Qub3d Demo";
        const std::string WINDOWTITLE_PAUSED = "Qub3d Demo - Paused";

        struct GameConfig
        {
            int WindowWidth = DEFAULTWINDOWWIDTH;
            int WindowHeight = DEFAULTWINDOWHEIGHT;

            static GameConfig *Get()
            {
                static GameConfig config;
                return &config;
            };

            void LoadFromFile(const std::string& filename);
        };
};