#pragma once

#include "camera/camera.h"
#include "game/map/map.h"
#include "scene/scene.h"
#include <SDL_events.h>
#include <memory>

// LIGHTBRINGER!
class Game
{
    friend class Editor;

    std::unique_ptr<Scene> m_Scene = nullptr;
    std::unique_ptr<Map> m_Map = nullptr; // math representation of level
    std::unique_ptr<Camera> m_Camera = nullptr;

    float m_DeltaTime;
public:
    Game();
    bool Init();
    void Update(float delta_time);
    void Draw();
    void PollEvents(SDL_Event& e);
private:
};