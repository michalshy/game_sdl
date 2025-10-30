#pragma once
#include "backends/imgui_impl_sdl2.h"


class Editor
{
    bool m_Demo = true;
public:
    bool Init(SDL_Window* window, SDL_Renderer* renderer);
    void OnFrame();
    void Run();
    void PreRender();
    void PostRender();
    void Exit();
    void PollEvents(SDL_Event& event);
};