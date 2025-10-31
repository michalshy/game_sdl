#include "game.h"
#include "scene/scene.h"
#include "scene/entity.h"
#include "scene/components.h"
#include "renderer/renderer.h"
#include <memory>

Game::Game()
{
    m_Scene = std::make_unique<Scene>();
    m_Level = std::make_unique<Level>();
}

bool Game::Init()
{
    if(!m_Scene)
        return false;

    if(!m_Level || !m_Level->InitLevel())
        return false;

    // lets add some debug entites
    Entity quad = m_Scene->CreateEntity();
    quad.AddComponent<CoSprite>();
    quad.AddComponent<CoTransform>();

    return true;
}

void Game::OnFrame()
{
    for(auto [ent, sprite, transform] : m_Scene->View<CoSprite, CoTransform>().each())
    {
        Renderer::DrawQuad(transform.transform, sprite.color);
    }
}

