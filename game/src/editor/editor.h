#pragma once
#include "backends/imgui_impl_sdl2.h"
#include <SDL_video.h>

class Editor
{
    SDL_GLContext m_Context;
    SDL_Window* m_Window;
public:
    bool Init(SDL_Window* window, SDL_GLContext context);
    void OnFrame();
    void PreRender();
    void PostRender();
    void Exit();
    void PollEvents(SDL_Event& event);
private:
    void UpdateUI();
};