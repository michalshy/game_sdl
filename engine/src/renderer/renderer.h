#pragma once

#include <SDL_render.h>
#include <SDL_video.h>
class Renderer
{
    SDL_Window* m_Window;
    SDL_GLContext m_Context;
public:
    bool Init(SDL_Window* window, SDL_GLContext m_Context);
    void PreRender();
    void PostRender();
    void Exit();
};