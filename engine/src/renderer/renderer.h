#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <glm/glm.hpp>
#include "shader.h"
#include <memory>

class Window; 

class Renderer
{
public:
    static bool Init(SDL_Window* window);
    static void Shutdown();
    
    static void BeginFrame();
    static void EndFrame();  
    static void PostFrame();  
    
    static void SetClearColor(const glm::vec4& color);
    
    static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);

private:
    struct RendererData
    {
        SDL_Window* window_raw = nullptr;
        uint32_t QuadVAO = 0;
        Shader QuadShader;
        glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
    };
    static std::unique_ptr<RendererData> s_Data;

    static void SetupOpenGLState();
};