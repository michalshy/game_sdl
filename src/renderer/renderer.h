#pragma once

#include <SDL_render.h>
class Renderer
{
    SDL_Renderer* renderer;
    SDL_Window* window;
public:
    bool Init(SDL_Window* window);
    void PreRender();
    void PostRender();
    void Exit();

    SDL_Renderer* GetRawRenderer();
    SDL_Window* GetRawWIndow();
};