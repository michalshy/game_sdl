#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shut down SDL
void close();

SDL_Texture* loadTexture(std::string path);

//The window we will render
SDL_Window* gWindow = nullptr;

// The surface contained by the window
SDL_Renderer* gRenderer = nullptr;

//Currently displayed texture
SDL_Texture* gTexture = nullptr;

bool init()
{
    bool success = true;

    if((SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else {

        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(!gWindow) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == nullptr)
            {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

    return success;
}

void close()    
{
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(!loadedSurface)
    {
        std::cout << "Unable to load image! SDL Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    
        if(!newTexture)
        {
            std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
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
            bool quit = false;

            SDL_Event e;

            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                        quit = true;
                }

                SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(gRenderer);

                SDL_Rect fillRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
                SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
                SDL_RenderFillRect(gRenderer, &fillRect);

                SDL_Rect outlineRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH * 2/3, SCREEN_HEIGHT*2/3};
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xff);
                SDL_RenderDrawRect(gRenderer, &outlineRect);

                //Draw blue horizontal line
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );        
                SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

                //Draw vertical line of yellow dots
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
                for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
                {
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
                }

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    close();
    return 0;
}