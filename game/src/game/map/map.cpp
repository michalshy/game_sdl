#include "map.h"
#include "map_consts.h"
#include "log.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <random>
#include "scene/components.h"
#include "scene/entity.h"

constexpr float wall_chance = 0.45f;
constexpr int iterations = 10;
constexpr int survival_threshold = 3;
constexpr int birth_threshold = 6;
constexpr int tile_size = 10;

Map::Map()
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

bool Map::Init(Scene* scene)
{
    if(!InitMap(scene))
        return false;

    LOG_DEBUG("Initialized Level");
    return true;
}

int Map::GetSeed()
{
    return seed;
}

bool Map::InitMap(Scene* scene)
{
    seed = std::random_device{}();
    //seed = 4164015880;
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

    DefineEntites(scene);
    return true;
}

bool Map::Birth(int y, int x)
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

bool Map::Survival(int y, int x)
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

void Map::DefineEntites(Scene* scene)
{
    glm::vec3 start_position = {0.0f, 0.0f, 0.0f};
    for(const auto& row : map_grid)
    {
        for(const auto& column : row)
        {
            Entity quad = scene->CreateEntity();
            glm::vec3 scale = {tile_size, tile_size, 1.0f};
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, start_position);
            model = glm::scale(model, scale);
            quad.AddComponent<CoTransform>(model);
            quad.AddComponent<CoSprite>(column == 1 ? glm::vec4{0.0f, 0.0f, 0.0f, 1.0f} : glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
            
            start_position += glm::vec3(tile_size, 0, 0);
        }
        start_position += glm::vec3(-start_position.x, tile_size, 0);
    }
}