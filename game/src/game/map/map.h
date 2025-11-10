#pragma once

// Level class of Lightbringer Game
// Simple grid defined by cellular automata algorithm
#include "scene/scene.h"
#include <random>
#include <vector>
#include "game/game_components.h"
#include "game/player/player.h"
class Map
{
    // Leaving int here since 
    // it might be used as different types of obstacles
    int seed;
    std::vector<std::vector<TileType>> map_grid;
    std::vector<std::vector<float>> light_map;
    Scene* m_Scene;
    std::mt19937 rng;
public:
    Map();
    bool Init(Scene* scene);
    glm::vec3 CheckBounds(Player& player);
    int GetSeed();
    void RunCycle();
    void Update();
    const std::vector<std::vector<float>>& GetLightMap() { return light_map; }
private:
    void UpdateLightMaps();
    void UpdateLightMap(const glm::vec2& light_pos_world, float radius, float intensity = 1.0f); 
    void Cycle();
    bool InitMap(Scene* scene);
    bool Birth(int y, int x);
    bool Survival(int y, int x);
    int CountWallNeighbors(int y, int x);
    void DefineEntites(Scene* scene);
    void ComputeEnemies();
    void ComputeAllies();
    void ComputeResources();
    void ComputeLight();
    glm::vec4 ComputeColors(int i, int j);
};