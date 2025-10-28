#include "level.h"
#include "game/level/level_consts.h"
#include "log.h"
#include <string>

Level::Level()
{
    map_grid.resize(GRID_DIMENSIONS.y);
    for(auto& el : map_grid)
    {
        el.resize(GRID_DIMENSIONS.x);
    }
}

bool Level::InitLevel()
{
    if(!InitMap())
        return false;

    LOG_DEBUG("Initialized Level");
    return true;
}

bool Level::InitMap()
{
    // fill sides with 0 // obstacle

    PrintMap();
    return true;
}

void Level::PrintMap()
{
    std::string cols = "";
    for(const auto& row : map_grid)
    {
        cols = "";
        for(const auto& column : row)
        {
            cols += std::to_string(column);
        }
        LOG_DEBUG(cols);
    }
}