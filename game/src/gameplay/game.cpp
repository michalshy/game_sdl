#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <spdlog/spdlog.h>
#include "log.h"
#include "game.h"


Game::Game()
{
    window = std::make_unique<Window>();
    renderer = std::make_unique<Renderer>();

#ifdef BUILD_WITH_EDITOR
    editor = std::make_unique<Editor>();
#endif
}

bool Game::Init()
{
    spdlog::set_level(LOG_LEVEL_DEBUG);

    if (!window || !renderer)
        return false;

    if(!window->Init())
        return false;

    if(!renderer->Init(window->GetWindowRaw(), window->GetContextRaw()))
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

void Game::Run()
{
    if(!initialized)
        return;

    while(!quit)
    {
        PollEvents();
        OnFrame();

#ifdef BUILD_WITH_EDITOR
        editor->Run();
#endif

        // game actions

        Render();
    }

    Exit();
}

void Game::Exit()
{
#ifdef BUILD_WITH_EDITOR
    editor->Exit();
#endif
    renderer->Exit();
    window->Exit();

    SDL_Quit();
}

void Game::PollEvents()
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

void Game::OnFrame()
{
#ifdef BUILD_WITH_EDITOR
    editor->OnFrame();
#endif
}

void Game::Render()
{
#ifdef BUILD_WITH_EDITOR
    editor->PreRender();
#endif
    renderer->PreRender();
#ifdef BUILD_WITH_EDITOR
    editor->PostRender();
#endif
    renderer->PostRender();
}