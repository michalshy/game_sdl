#pragma once

// Level class of Lightbringer Game
// Simple grid defined by cellular automata algorithm
#include "scene/scene.h"
#include <random>
#include <vector>
#include "game/game_components.h"
class Map
{
    // Leaving int here since 
    // it might be used as different types of obstacles
    int seed;
    std::vector<std::vector<TileType>> map_grid;
    Scene* m_Scene;
    std::mt19937 rng;
public:
    Map();
    bool Init(Scene* scene);
    void Draw();
    int GetSeed();
    void RunCycle();
private:
    void Cycle();
    bool InitMap(Scene* scene);
    bool Birth(int y, int x);
    bool Survival(int y, int x);
    int CountWallNeighbors(int y, int x);
    void DefineEntites(Scene* scene);
};