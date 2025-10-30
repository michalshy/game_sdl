#pragma once
#include <SDL_video.h>

class Window
{
    SDL_Window* window;
    SDL_GLContext context;
public:
    bool Init();
    SDL_Window* GetWindowRaw();
    SDL_GLContext* GetContextRaw();
    void Exit();
};