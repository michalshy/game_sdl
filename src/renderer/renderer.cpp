#include "renderer.h"
#include <iostream>

bool Renderer::Init(SDL_Window* _window)
{
    if(!_window)
        return false;

    window = _window;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::Render()
{
    SDL_RenderPresent( renderer );
}

void Renderer::Exit()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
}