#pragma once

#include "game/level/level.h"
#include "scene/scene.h"
#include <memory>

// LIGHTBRINGER!
class Game
{
    std::unique_ptr<Scene> m_Scene = nullptr;
    std::unique_ptr<Level> m_Level = nullptr; // math representation of level
public:
    Game();
    bool Init();
    void OnFrame();
};