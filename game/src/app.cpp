#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <spdlog/spdlog.h>
#include "log.h"
#include "app.h"


App::App()
{
    window = std::make_unique<Window>();
    game = std::make_unique<Game>();
#ifdef BUILD_WITH_EDITOR
    editor = std::make_unique<Editor>();
#endif
}

bool App::Init()
{
    spdlog::set_level(LOG_LEVEL_DEBUG);

    if (!window || !window->Init())
        return false;

    if (!game || !game->Init())
        return false;

#ifdef BUILD_WITH_EDITOR

    if(!editor || !editor->Init(window->GetWindowRaw(), window->GetContextRaw()))
    LOG_DEBUG("Initialized Game with editor");
#else
    LOG_DEBUG("Initialized Game");
#endif
    initialized = true;
    return true;
}

void App::Run()
{
    if(!initialized)
        return;

    while(!quit)
    {
        PollEvents();
        OnFrame();

        PostFrame();
    }

    Exit();
}

void App::Exit()
{
#ifdef BUILD_WITH_EDITOR
    editor->Exit();
#endif
    window->Exit();

    SDL_Quit();
}

void App::PollEvents()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
#ifdef BUILD_WITH_EDITOR
        editor->PollEvents(e);
#endif
        if(e.type == SDL_QUIT)
            quit = true;
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(window->GetWindowRaw()))
            quit = true;
    }
}

void App::OnFrame()
{
#ifdef BUILD_WITH_EDITOR
    editor->OnFrame();
#endif
    game->OnFrame();
}

void App::PostFrame()
{
#ifdef BUILD_WITH_EDITOR
    editor->PreRender();
#endif
    window->Clear();
#ifdef BUILD_WITH_EDITOR
    editor->PostRender();
#endif
    window->SwapBuffers();
}