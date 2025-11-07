#pragma once

#include "scene/scene.h"
#include <glm/fwd.hpp>
#include <memory>

class CollisionManager
{
    std::shared_ptr<Scene> m_Scene;
public:
    CollisionManager(std::shared_ptr<Scene> scene) : m_Scene(scene) {}
    void Update();
private:
    bool CheckAABB(glm::mat4& a_pos, glm::mat4& b_pos, glm::ivec2& a_size, glm::ivec2& b_size);
    void ResolveAABB(glm::mat4& a_pos, glm::mat4& b_pos, glm::ivec2& a_size, glm::ivec2& b_size);
};