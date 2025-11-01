#pragma once

#include "scene/scene.h"
#include "scene/entity.h"

enum class PlayerMovement {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Player
{
    Entity m_PlayerEntity;
public:
    Player(Entity&& entity);
    void HandleInput(float delta_time);
    void ToggleInput(bool state);

private:
    struct PlayerState
    {
        float movement_speed = 10.0f;

        bool ignore_movement = true;
    } m_State;

    void ProcessKeyboard(PlayerMovement dir, float delta_time);
};