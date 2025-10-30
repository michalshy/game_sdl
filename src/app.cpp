#include "app.h"
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <spdlog/spdlog.h>
#include "log.h"


App::App()
{
    window = std::make_unique<Window>();
    renderer = std::make_unique<Renderer>();
    game = std::make_unique<Game>();
    editor = std::make_unique<Editor>();
}

bool App::Init()
{
    spdlog::set_level(LOG_LEVEL_DEBUG);

    if (!window || !renderer || !game || !editor)
        return false;

    if(!window->Init())
        return false;

    if(!renderer->Init(window->GetWindowRaw()))
        return false;

    if(!game->Init())
        return false;

    if(!editor->Init(renderer->GetRawWIndow(), renderer->GetRawRenderer()))
        return false;

    LOG_DEBUG("Initialized Application");
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

        // editor actions
        editor->Run();
        // game actions

        Render();
    }

    Exit();
}

void App::Exit()
{
    renderer->Exit();
    window->Exit();

    IMG_Quit();
    SDL_Quit();
}

void App::PollEvents()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        editor->PollEvents(e);

        if(e.type == SDL_QUIT)
            quit = true;
    }
}

void App::OnFrame()
{
    editor->OnFrame();
}

void App::Render()
{
    editor->PreRender();
    renderer->PreRender();
    editor->PostRender();
    renderer->PostRender();
}