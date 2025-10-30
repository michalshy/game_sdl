#include "window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL_video.h>
#include <iostream>


constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

bool Window::Init()
{
    if((SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else {

        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(!window) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }
        else {
            
        }
    }
    return true;
}

SDL_Window* Window::GetWindowRaw()
{
    return window;
}

void Window::Exit()
{
    SDL_DestroyWindow(window);
    window = nullptr;
}