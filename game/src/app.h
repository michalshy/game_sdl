#pragma once
#include "editor/editor.h"
#include "game/game.h"
#include "window/window.h"
#include <memory>

#define BUILD_WITH_EDITOR 1

// Serves as entry point to application
// More project dependent functions shall be deeper
class App
{
    bool initialized = false;
    bool quit = false;

    std::unique_ptr<Window> window = nullptr;
    std::unique_ptr<Game> game = nullptr;
#ifdef BUILD_WITH_EDITOR
    std::unique_ptr<Editor> editor = nullptr;
#endif

public:
    App();
    bool Init();
    void Run();
    void Exit();
private:
    void PollEvents();
    void OnFrame();
    void PostFrame();
};