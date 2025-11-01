#include "game.h"
#include "log.h"
#include "scene/scene.h"
#include "scene/entity.h"
#include "scene/components.h"
#include "renderer/renderer.h"
#include <glm/ext/matrix_transform.hpp>
#include <memory>
#include "glm/glm.hpp"

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
    glm::vec3 position = {1280.0f / 2.0f, 720.0f / 2.0f, 0.0f};
    glm::vec3 scale = {100.0f, 100.0f, 1.0f};
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    quad.AddComponent<CoTransform>(model);

    return true;
}

void Game::OnFrame()
{
    for(auto [ent, sprite, transform] : m_Scene->View<CoSprite, CoTransform>().each())
    {
        Renderer::DrawQuad(transform.transform, sprite.color);
    }
}

