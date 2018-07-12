#pragma once
#include <strings>

namespace settings
{

const int DEFAULTWINDOWWIDTH = 1280
const int DEFAULTWINDOWHEIGHT = 720

string WINDOWTITLE = "Qub3d Demo"
string WINDOWTITLE_PAUSED = "Qub3d Demo - Paused"

struct GameConfig
{
    int WindowWidth = DEFAULTWINDOWWIDTH;
    int WindowHeight = DEFAULTWINDOWHEIGHT;

    static GameConfig *Get()
    {
        static GameConfig c;
        return &c;
    }
};

} // namespace settings