#pragma once

#include "window/window.h"
#include "renderer/renderer.h"
#include <memory>

class App
{
    bool initialized = false;
    bool quit = false;

    std::unique_ptr<Window> window = nullptr;
    std::unique_ptr<Renderer> renderer = nullptr;
public:
    App();
    bool Init();
    void Run();
    void Exit();
private:
    void PollEvents();
};