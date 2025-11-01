#include "renderer.h"
#include <GL/glew.h>
#include "window/window.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>

std::unique_ptr<Renderer::RendererData> Renderer::s_Data = nullptr;

struct QuadVertex
{
    glm::vec3 Position;
    glm::vec4 Color;
};

void Renderer::SetupOpenGLState()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_MULTISAMPLE);
}

bool Renderer::Init(SDL_Window* window)
{
    s_Data = std::make_unique<RendererData>();
    s_Data->window_raw = window;

    if(!window)
        return false;

    uint32_t VBO, IBO;
    float vertices[] = {
        // Position (X, Y, Z)
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    uint32_t indices[] = { 0, 1, 2, 2, 3, 0 }; 
    
    glGenVertexArrays(1, &s_Data->QuadVAO);
    glBindVertexArray(s_Data->QuadVAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Configure Vertex Attributes (Position is layout location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
    s_Data->QuadShader = Shader("res/shaders/base.vert", "res/shaders/base.frag");
    
    s_Data->ProjectionMatrix = glm::ortho(0.0f, (float)1280, 0.0f, (float)720, -1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    return true;
}

void Renderer::BeginFrame()
{
    int display_w, display_h;
    SDL_GL_GetDrawableSize(s_Data->window_raw, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

void Renderer::Shutdown()
{
    glDeleteProgram(s_Data->QuadShader.GetId());
    glDeleteVertexArrays(1, &s_Data->QuadVAO);

    s_Data.reset();
}

void Renderer::SetClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::EndFrame()
{
    // tbd
}

void Renderer::PostFrame()
{
    SDL_GL_SwapWindow(s_Data->window_raw);
}

void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
    if (s_Data->QuadShader.GetId() == 0) {
        std::cerr << "Renderer not initialized!" << std::endl;
        return;
    }
    
    s_Data->QuadShader.Use();
    glBindVertexArray(s_Data->QuadVAO);

    s_Data->QuadShader.SetMat4("u_Transform", transform);
    s_Data->QuadShader.SetMat4("u_ViewProjection", s_Data->ProjectionMatrix);
    s_Data->QuadShader.SetFloat4("u_Color", color.r, color.g, color.b, color.a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); 

    glBindVertexArray(0);
    glUseProgram(0);
}