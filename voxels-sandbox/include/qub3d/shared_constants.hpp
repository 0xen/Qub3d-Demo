#pragma once

#define Q3_FULLSCREEN

#ifdef Q3_FULLSCREEN
    #define Q3_WINDOWWIDTH 1920  
    #define Q3_WINDOWHEIGHT 1080
#else
    #define Q3_WINDOWWIDTH 640  
    #define Q3_WINDOWHEIGHT 480
#endif

#define Q3_WINDOWTITLE "Qub3d Demo"
#define Q3_WINDOWTITLE_PAUSED "Qub3d Demo - Paused"