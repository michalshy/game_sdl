#pragma once

#include <SDL_render.h>
class Renderer
{
    SDL_Renderer* renderer;
    SDL_Window* window;
public:
    bool Init(SDL_Window* window);
    void Render();
    void Exit();
};