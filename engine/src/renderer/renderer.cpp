#include "renderer.h"
#include <GL/glew.h>

bool Renderer::Init(SDL_Window* window, SDL_GLContext context)
{
    if(!window || !context)
        return false;

    m_Window = window;
    m_Context = context;

    return true;
}

void Renderer::PreRender()
{
    int display_w, display_h;
    SDL_GL_GetDrawableSize(m_Window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::PostRender()
{
    SDL_GL_SwapWindow(m_Window);
}

void Renderer::Exit()
{
    // empty
}