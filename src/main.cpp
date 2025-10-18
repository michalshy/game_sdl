#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int main(int, char*[]) {
    SDL_Window* window = nullptr;

    SDL_Surface* screenSurface = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    }
    else {
        window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(!window)
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));

            SDL_UpdateWindowSurface(window);
            SDL_Event e; bool quit = false; while(quit == false){while(SDL_PollEvent(&e)) if(e.type == SDL_QUIT) quit = true;}
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}