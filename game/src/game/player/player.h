#pragma once

#include "camera/camera.h"
#include "scene/scene.h"
#include "scene/entity.h"
#include <memory>

struct BlockFlag
{
    bool skip = false;
    bool triggered = false;

    void clear()
    {
        skip = false;
        triggered = false;
    }
};

enum class PlayerMovement {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Player
{
    Entity m_PlayerEntity;
    std::shared_ptr<Camera> m_Camera;
public:
    Player(Entity&& entity);
    bool Init(std::shared_ptr<Camera> camera);
    void HandleInput(float delta_time);
    void HandleCamera(float delta_time);
    void ToggleInput(bool state);
    void Update(float delta_time, Scene* scene);
    private:
    struct PlayerState
    {
        float movement_speed = 10.0f;
        glm::vec3 last_move;
        bool ignore_movement = false;
        BlockFlag block_input_left;
        BlockFlag block_input_right;
        BlockFlag block_input_up;
        BlockFlag block_input_down;
    } m_State;
    
    void ProcessKeyboard(PlayerMovement dir, float delta_time);
    void CheckCollision(glm::vec3 playerPos, glm::ivec2 playerSize, glm::vec3 otherPos, glm::ivec2 otherSize);
    void ClearBlocks();
};