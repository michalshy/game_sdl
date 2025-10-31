#pragma once

// Level class of Lightbringer Game
// Simple grid defined by cellular automata algorithm
#include "level_consts.h"
#include <vector>
class Level
{
    // Leaving int here since 
    // it might be used as different types of obstacles
    std::vector<std::vector<int>> map_grid;
public:
    Level();
    bool InitLevel();

private:
    bool InitMap();
    bool Birth(int y, int x);
    bool Survival(int y, int x);
    void PrintMap();
};