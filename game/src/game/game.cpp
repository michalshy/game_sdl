#include "game.h"
#include "camera/camera.h"
#include "scene/scene.h"
#include "scene/components.h"
#include "renderer/renderer.h"
#include <SDL_events.h>
#include <glm/ext/matrix_transform.hpp>
#include <memory>

Game::Game()
{
    m_Scene = std::make_unique<Scene>();
    m_Map = std::make_unique<Map>();
    m_Camera = std::make_unique<Camera>(1280.0f, 720.0f);
    m_Player = std::make_unique<Player>(m_Scene->CreateEntity());
}

bool Game::Init()
{
    if(!m_Scene)
        return false;

    if(!m_Map || !m_Map->Init(m_Scene.get()))
        return false;

    return true;
}

void Game::Update(float delta_time)
{
    m_DeltaTime = delta_time;

    m_Player->HandleInput(m_DeltaTime);
}

void Game::Draw()
{
    Renderer::SetProjectionMatrix(m_Camera->GetViewProjectionMatrix());

    Renderer::Bind();
    for(auto [ent, sprite, transform] : m_Scene->View<CoSprite, CoTransform>().each())
    {
        Renderer::DrawQuad(transform.transform, sprite.color);
    }
    Renderer::Unbind();
}

void Game::PollEvents(SDL_Event& /*e*/)
{
    //tbd
}


