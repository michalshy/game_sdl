#pragma once
#include <SDL_video.h>

class Window
{
    SDL_Window* m_Window;
    SDL_GLContext m_Context;
public:
    bool Init();
    SDL_Window* GetWindowRaw();
    SDL_GLContext GetContextRaw();
    void Clear();
    void SwapBuffers();
    void Exit();
};