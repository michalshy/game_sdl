#pragma once
#include "editor/editor.h"
#include "renderer/renderer.h"
#include "window/window.h"
#include <memory>

#define BUILD_WITH_EDITOR 1

class Game
{
    bool initialized = false;
    bool quit = false;

    std::unique_ptr<Window> window = nullptr;
    std::unique_ptr<Renderer> renderer = nullptr;
#ifdef BUILD_WITH_EDITOR
    std::unique_ptr<Editor> editor = nullptr;
#endif

public:
    Game();
    bool Init();
    void Run();
    void Exit();
private:
    void PollEvents();
    void OnFrame();
    void Render();
};