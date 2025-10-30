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

void Renderer::PreRender()
{
    SDL_SetRenderDrawColor(renderer, 25, 30, 38, 255);
    SDL_RenderClear(renderer);
}

void Renderer::PostRender()
{
    SDL_RenderPresent( renderer );
}

void Renderer::Exit()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
}

SDL_Renderer* Renderer::GetRawRenderer()
{
    return renderer;
}

SDL_Window* Renderer::GetRawWIndow()
{
    return window;
}   