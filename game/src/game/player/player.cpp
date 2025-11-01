#include "player.h"
#include "scene/entity.h"
#include "scene/components.h"
#include "glm/glm.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include "game/map/map_consts.h"
#include <SDL2/SDL.h>

constexpr glm::ivec2 PLAYER_SIZE{6,12};

Player::Player(Entity&& entity) : m_PlayerEntity(entity) 
{
    const glm::vec3 start_position {(GRID_DIMENSIONS.x/2)*TILE_SIZE, (GRID_DIMENSIONS.y/2)*TILE_SIZE, 0.1f};
    // lets create components
    glm::mat4 model = glm::translate(glm::mat4(1.0f), start_position);
    model = glm::scale(model, glm::vec3(PLAYER_SIZE.x, PLAYER_SIZE.y, 1.0f));
    m_PlayerEntity.AddComponent<CoTransform>(model);
    m_PlayerEntity.AddComponent<CoSprite>(glm::vec4{0.0f, 0.0f, 1.0f, 1.0f});
    m_PlayerEntity.AddComponent<CoCollider>();
}

void Player::HandleInput(float delta_time)
{
    if(m_State.ignore_movement)
        return;
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
        ProcessKeyboard(PlayerMovement::UP, delta_time);
    if (state[SDL_SCANCODE_S])
        ProcessKeyboard(PlayerMovement::DOWN, delta_time);
    if (state[SDL_SCANCODE_A])
        ProcessKeyboard(PlayerMovement::LEFT, delta_time);
    if (state[SDL_SCANCODE_D])
        ProcessKeyboard(PlayerMovement::RIGHT, delta_time);
}

void Player::ToggleInput(bool state)
{
    m_State.ignore_movement = !state;
}

void Player::ProcessKeyboard(PlayerMovement dir, float delta_time)
{
    float velocity = m_State.movement_speed * delta_time;

    if (dir == PlayerMovement::UP)    m_PlayerEntity.GetComponent<CoTransform>().Translate(glm::vec3{0.0f, velocity, 0.0f});
    if (dir == PlayerMovement::DOWN)  m_PlayerEntity.GetComponent<CoTransform>().Translate(glm::vec3{0.0f, -velocity, 0.0f});
    if (dir == PlayerMovement::LEFT)  m_PlayerEntity.GetComponent<CoTransform>().Translate(glm::vec3{-velocity, 0.0f, 0.0f});
    if (dir == PlayerMovement::RIGHT) m_PlayerEntity.GetComponent<CoTransform>().Translate(glm::vec3{velocity, 0.0f, 0.0f});
}
