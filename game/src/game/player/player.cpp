#include "player.h"
#include "camera/camera.h"
#include "log.h"
#include "scene/entity.h"
#include "scene/components.h"
#include "glm/glm.hpp"
#include <glm/common.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include "game/map/map_consts.h"
#include <SDL2/SDL.h>
#include <memory>

constexpr glm::ivec2 PLAYER_SIZE{6,12};
constexpr float COLLISION_MARGIN = 0.5f;

Player::Player(Entity&& entity) : m_PlayerEntity(entity) 
{
    const glm::vec3 start_position {(GRID_DIMENSIONS.x/2)*TILE_SIZE, (GRID_DIMENSIONS.y/2)*TILE_SIZE, 0.1f};
    // lets create components
    glm::mat4 model = glm::translate(glm::mat4(1.0f), start_position);
    model = glm::scale(model, glm::vec3(PLAYER_SIZE.x, PLAYER_SIZE.y, 1.0f));
    m_PlayerEntity.AddComponent<CoTransform>(model);
    m_PlayerEntity.AddComponent<CoSprite>(glm::vec4{0.0f, 0.0f, 1.0f, 1.0f});
    m_PlayerEntity.AddComponent<CoCollider>(true, ColliderType::BOX, PLAYER_SIZE.x);
}

bool Player::Init(std::shared_ptr<Camera> camera)
{
    if(!camera)
        return false;

    m_Camera = camera;
    return true;
}

void Player::HandleInput(float delta_time)
{
    if(m_State.ignore_movement)
        return;
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W] && !m_State.block_input_up.triggered)
        ProcessKeyboard(PlayerMovement::UP, delta_time);
    if (state[SDL_SCANCODE_S] && !m_State.block_input_down.triggered)
        ProcessKeyboard(PlayerMovement::DOWN, delta_time);
    if (state[SDL_SCANCODE_A] && !m_State.block_input_left.triggered)
        ProcessKeyboard(PlayerMovement::LEFT, delta_time);
    if (state[SDL_SCANCODE_D] && !m_State.block_input_right.triggered)
        ProcessKeyboard(PlayerMovement::RIGHT, delta_time);

    m_State.last_move = m_PlayerEntity.GetComponent<CoTransform>().transform[3];

    HandleCamera(delta_time);
}

void Player::HandleCamera(float /*delta_time*/) // TODO: USE DELTA TIME TO SMOOTH looking IN INPUT DIRECTIOn
{
    glm::vec3 pos = glm::vec3(m_PlayerEntity.GetComponent<CoTransform>().transform[3]); // x,y,z
    m_Camera->SetPosition(pos);
}

void Player::ToggleInput(bool state)
{
    m_State.ignore_movement = !state;
}

void Player::Update(float delta_time, Scene* scene)
{
    auto& playerTransform = m_PlayerEntity.GetComponent<CoTransform>();

    glm::vec3 playerPos = glm::vec3(playerTransform.transform[3]);

    ClearBlocks();
    auto view = scene->View<CoTransform, CoCollider>();
    for (auto [entity, transform, collider] : view.each())
    {
        if(!collider.on)
            continue;
        
        // Don't collide with self
        if(transform.transform == m_PlayerEntity.GetComponent<CoTransform>().transform)
            continue;

        glm::vec3 otherPos = glm::vec3(transform.transform[3]);
        CheckCollision(playerPos, PLAYER_SIZE, otherPos, glm::ivec2{ collider.size, collider.size });
    }
    HandleInput(delta_time);
}

void Player::CheckCollision(
    glm::vec3 playerPos, glm::ivec2 playerSize,
    glm::vec3 otherPos, glm::ivec2 otherSize)
{
    // AABB overlap test
    bool overlapX = playerPos.x < otherPos.x + otherSize.x &&
                    playerPos.x + playerSize.x > otherPos.x;

    bool overlapY = playerPos.y < otherPos.y + otherSize.y &&
                    playerPos.y + playerSize.y > otherPos.y;

    if (!(overlapX && overlapY))
        return;

    // Penetration values (amount the boxes overlap)
    float penLeft   = (playerPos.x + playerSize.x) - otherPos.x;
    float penRight  = (otherPos.x + otherSize.x) - playerPos.x;
    float penBottom = (playerPos.y + playerSize.y) - otherPos.y;
    float penTop    = (otherPos.y + otherSize.y) - playerPos.y;

    // Choose smallest axis overlap → collision direction
    float minPen = std::min(std::min(penLeft, penRight),
                            std::min(penBottom, penTop));

    // Horizontal collision — allow vertical sliding
    if (minPen == penLeft  && penLeft  > COLLISION_MARGIN)
    {
        m_State.block_input_right.triggered = true;
    }
    else if (minPen == penRight && penRight > COLLISION_MARGIN)
    {
        m_State.block_input_left.triggered = true;
    }

    // Vertical collision — allow horizontal sliding
    if (minPen == penBottom && penBottom > COLLISION_MARGIN)
    {
        m_State.block_input_up.triggered = true;
    }
    else if (minPen == penTop && penTop > COLLISION_MARGIN)
    {
        m_State.block_input_down.triggered = true;
    }
}

void Player::ClearBlocks()
{
    m_State.block_input_left.clear();
    m_State.block_input_right.clear();
    m_State.block_input_down.clear();
    m_State.block_input_up.clear();
}


void Player::ProcessKeyboard(PlayerMovement dir, float delta_time)
{
    float velocity = m_State.movement_speed * delta_time;

    if (dir == PlayerMovement::UP)    m_PlayerEntity.GetComponent<CoTransform>().Translate(glm::vec3{0.0f, velocity, 0.0f});
    if (dir == PlayerMovement::DOWN)  m_PlayerEntity.GetComponent<CoTransform>().Translate(glm::vec3{0.0f, -velocity, 0.0f});
    if (dir == PlayerMovement::LEFT)  m_PlayerEntity.GetComponent<CoTransform>().Translate(glm::vec3{-velocity, 0.0f, 0.0f});
    if (dir == PlayerMovement::RIGHT) m_PlayerEntity.GetComponent<CoTransform>().Translate(glm::vec3{velocity, 0.0f, 0.0f});
}
