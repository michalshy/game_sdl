#include "level.h"
#include "game/level/level_consts.h"
#include "log.h"
#include <string>
#include <random>

constexpr float wall_chance = 0.45f;
constexpr int iterations = 10;
constexpr int survival_threshold = 3;
constexpr int birth_threshold = 6;

Level::Level()
{
    for(int y = 0; y < GRID_DIMENSIONS.y; y++)
    {
        map_grid.push_back({});
        for(int x = 0; x < GRID_DIMENSIONS.x; x++)
        {
            map_grid[y].push_back(1);
        }
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
    unsigned int seed = std::random_device{}();
    seed = 4164015880;
    LOG_DEBUG("Creating level for seed: {}", seed);
    std::mt19937 rng(seed);
    std::uniform_real_distribution<> dist(0.0f,1.0f);
    for(int y = 1; y < GRID_DIMENSIONS.y - 1; y++)
    {
        for(int x = 1; x < GRID_DIMENSIONS.x - 1; x++)
        {
            map_grid[y][x] = dist(rng) > wall_chance ? 0 : 1;
        }
    } 

    for(int i = 0; i < iterations; i++)
    {
        for(int y = 1; y < GRID_DIMENSIONS.y - 1; y++)
        {
            for(int x = 1; x < GRID_DIMENSIONS.x - 1; x++)
            {
                if(!Survival(y,x))
                {
                    map_grid[y][x] = 0;
                }
                else if(Birth(y, x))
                {
                    map_grid[y][x] = 1;
                }
            }
        } 
    }

    PrintMap();
    return true;
}

bool Level::Birth(int y, int x)
{
    int neighbours = 0;
    if(map_grid[y-1][x])
        ++neighbours;
    if(map_grid[y-1][x-1])
        ++neighbours;
    if(map_grid[y][x-1])
        ++neighbours;
    if(map_grid[y][x+1])
        ++neighbours;
    if(map_grid[y+1][x+1])
        ++neighbours;
    if(map_grid[y+1][x])
        ++neighbours;
    if(map_grid[y+1][x-1])
        ++neighbours;
    if(map_grid[y-1][x+1])
        ++neighbours;

    return neighbours >= birth_threshold;
}

bool Level::Survival(int y, int x)
{
    int neighbours = 0;
    if(map_grid[y-1][x])
        ++neighbours;
    if(map_grid[y-1][x-1])
        ++neighbours;
    if(map_grid[y][x-1])
        ++neighbours;
    if(map_grid[y][x+1])
        ++neighbours;
    if(map_grid[y+1][x+1])
        ++neighbours;
    if(map_grid[y+1][x])
        ++neighbours;
    if(map_grid[y+1][x-1])
        ++neighbours;
    if(map_grid[y-1][x+1])
        ++neighbours;

    return neighbours >= survival_threshold;
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