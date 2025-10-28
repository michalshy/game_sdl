#pragma once
#include <SDL_video.h>

class Window
{
    SDL_Window* window;
public:
    bool Init();
    SDL_Window* GetWindowRaw();
    void Exit();
};