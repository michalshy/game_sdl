#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shut down SDL
void close();

//The window we will render
SDL_Window* gWindow = nullptr;

// The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

// THe image we will load and show
SDL_Surface* gHelloWorld = nullptr;

bool init()
{
    bool success = true;

    if((SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(!gWindow) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        }
        else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

    gHelloWorld = SDL_LoadBMP("res/hello.bmp");
    if(!gHelloWorld) {
        std::cout << "Unable to load image. SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = nullptr;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}

int main(int, char*[]) {

    if(!init())
    {
        std::cout << "Failed to initialize!" << std::endl;
    }
    else 
    {
        if(!loadMedia())
        {
            std::cout << "Failed to load media!" << std::endl;
        }
        else 
        {
            SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
            SDL_UpdateWindowSurface(gWindow);

            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }
    close();
    return 0;
}