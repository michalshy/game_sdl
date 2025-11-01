#pragma once

// Level class of Lightbringer Game
// Simple grid defined by cellular automata algorithm
#include "scene/scene.h"
#include <vector>
class Map
{
    // Leaving int here since 
    // it might be used as different types of obstacles
    int seed;
    std::vector<std::vector<int>> map_grid;
public:
    Map();
    bool Init(Scene* scene);
    void Draw();
    int GetSeed();
private:
    bool InitMap(Scene* scene);
    bool Birth(int y, int x);
    bool Survival(int y, int x);
    void DefineEntites(Scene* scene);
};