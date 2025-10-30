#include "window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL_video.h>
#include <iostream>
#include <GL/glew.h>
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

bool Window::Init()
{
    if((SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cout << "SDL Could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else {

        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        window = SDL_CreateWindow("Game",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
        if(!window) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }
        else {
            context = SDL_GL_CreateContext(window);
            if (!context) {
                std::cout << "Error: SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
                return false;
            }
            SDL_GL_MakeCurrent(window, context);

            glewExperimental = GL_TRUE;
            GLenum glew_err = glewInit();
            if (glew_err != GLEW_OK) {
                std::cout << "Error: glewInit failed: " << glewGetErrorString(glew_err) << std::endl;
                return false;
            }

            glGetError();

        }
    }
    return true;
}

SDL_Window* Window::GetWindowRaw()
{
    return window;
}

SDL_GLContext* Window::GetContextRaw()
{
    return &context;
}

void Window::Exit()
{
    SDL_DestroyWindow(window);
    window = nullptr;
}