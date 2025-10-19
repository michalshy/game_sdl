#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Starts SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shut down SDL
void close();

SDL_Surface* loadSurface(std::string path);

//The window we will render
SDL_Window* gWindow = nullptr;

// The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

// THe image we will load and show
SDL_Surface* gKeyPressSurfaces [ KEY_PRESS_SURFACE_TOTAL ];

// Currently displayed image
SDL_Surface* gCurrentSurface = nullptr;

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

    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("res/def.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr)
    {
        std::cout << "Failed to load default image!" << std::endl;
        success = false;
    }

    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface("res/down.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr)
    {
        std::cout << "Failed to load down image!" << std::endl;
        success = false;
    }

    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface("res/left.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr)
    {
        std::cout << "Failed to load left image!" << std::endl;
        success = false;
    }

    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface("res/up.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr)
    {
        std::cout << "Failed to load up image!" << std::endl;
        success = false;
    }

    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface("res/right.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr)
    {
        std::cout << "Failed to load right image!" << std::endl;
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surfaces
    for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = nullptr;
	}

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(!loadedSurface)
    {
        std::cout << "Unable to load image! SDL Error: " << SDL_GetError() << std::endl;
    }

    return loadedSurface;
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
            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                        quit = true;
                    else if(e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;
                        case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;
                        case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;
                        case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            break;
                        default:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                            break;
                        }
                    }
                }

                SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    close();
    return 0;
}