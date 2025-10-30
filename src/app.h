#pragma once

#include "window/window.h"
#include "renderer/renderer.h"
#include "game/game.h"
#include "editor.h"
#include <memory>


class App
{
    bool initialized = false;
    bool quit = false;

    std::unique_ptr<Window> window = nullptr;
    std::unique_ptr<Renderer> renderer = nullptr;
    std::unique_ptr<Game> game;
    std::unique_ptr<Editor> editor;
public:
    App();
    bool Init();
    void Run();
    void Exit();
private:
    void PollEvents();
    void OnFrame();
    void Render();
};