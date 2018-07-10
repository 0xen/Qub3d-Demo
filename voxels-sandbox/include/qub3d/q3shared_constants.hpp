#pragma once

//#define Q3_FULLSCREEN

#ifdef Q3_FULLSCREEN
    #define Q3_DEFAULTWINDOWWIDTH 1920  
    #define Q3_DEFAULTWINDOWHEIGHT 1080
#else
    #define Q3_DEFAULTWINDOWWIDTH 640  
    #define Q3_DEFAULTWINDOWHEIGHT 480
#endif

#define Q3_WINDOWTITLE "Qub3d Demo"
#define Q3_WINDOWTITLE_PAUSED "Qub3d Demo - Paused"

#define Q3_FOV 45.f

#define Q3_PIF 3.14159265359f
#define Q3_PID 3.14159265359

#define Q3_MAPSIZE 16

#define Q3_MOUSE_BUTTON_PLACE_BLOCK SDL_BUTTON_RIGHT
#define Q3_MOUSE_BUTTON_DESTROY_BLOCK SDL_BUTTON_LEFT

#define Q3_SPRITESIZE 32.f
#define Q3_NO_BLOCKS 2

struct Q3GameConfig {
    int WindowWidth = Q3_DEFAULTWINDOWWIDTH;
    int WindowHeight = Q3_DEFAULTWINDOWHEIGHT;

    static Q3GameConfig *Get() 
    {
        static Q3GameConfig c;
        return &c;
    }
};