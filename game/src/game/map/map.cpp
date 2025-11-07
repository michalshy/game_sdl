#include "map.h"
#include "game/game_components.h"
#include "map_consts.h"
#include "log.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <random>
#include "scene/components.h"
#include "scene/entity.h"

constexpr float wall_chance = 0.45f;
constexpr int iterations = 5;
constexpr int survival_threshold = 2;
constexpr int birth_threshold = 3;

Map::Map()
{
    for(int y = 0; y < GRID_DIMENSIONS.y; y++)
    {
        map_grid.push_back({});
        for(int x = 0; x < GRID_DIMENSIONS.x; x++)
        {
            map_grid[y].push_back(TileType::OBSTACLE);
        }
    }  
}

bool Map::Init(Scene* scene)
{
    if(!scene)
        return false;

    m_Scene = scene;
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
    rng = std::mt19937(seed);
    std::uniform_real_distribution<> dist(0.0f,1.0f);
    for(int y = 1; y < GRID_DIMENSIONS.y - 1; y++)
    {
        for(int x = 1; x < GRID_DIMENSIONS.x - 1; x++)
        {
            map_grid[y][x] = dist(rng) > wall_chance ? TileType::NONOBSTACLE : TileType::OBSTACLE;
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
                    map_grid[y][x] = TileType::NONOBSTACLE;
                }
                else if(Birth(y, x))
                {
                    map_grid[y][x] = TileType::OBSTACLE;
                }
            }
        } 
    }

    // Now we want to get to the middle of the map and declare empty square for the castle
    for(int i = 0; i < CASTLE_SIZE; i++)
    {
        for(int j = 0; j < CASTLE_SIZE; j++)
        {
            map_grid[GRID_DIMENSIONS.y/2 - CASTLE_SIZE/2 + i][GRID_DIMENSIONS.x/2 - CASTLE_SIZE/2 + j] = TileType::SPECIAL; // means special
        }   
    }

    DefineEntites(scene);
    return true;
}

bool Map::Birth(int y, int x)
{
    int neighbours = 0;
    if(map_grid[y-1][x] == TileType::OBSTACLE)
        ++neighbours;
    if(map_grid[y][x-1] == TileType::OBSTACLE)
        ++neighbours;
    if(map_grid[y][x+1] == TileType::OBSTACLE)
        ++neighbours;
    if(map_grid[y+1][x] == TileType::OBSTACLE)
        ++neighbours;

    return neighbours >= birth_threshold;
}

bool Map::Survival(int y, int x)
{
    int neighbours = 0;
    if(map_grid[y-1][x] == TileType::OBSTACLE)
        ++neighbours;
    if(map_grid[y][x-1] == TileType::OBSTACLE)
        ++neighbours;
    if(map_grid[y][x+1] == TileType::OBSTACLE)
        ++neighbours;
    if(map_grid[y+1][x] == TileType::OBSTACLE)
        ++neighbours;

    return neighbours >= survival_threshold;
}

void Map::DefineEntites(Scene* scene)
{
    glm::vec3 start_position = {0.0f, 0.0f, 0.0f};
    for(int i = 0; i < (int)map_grid.size(); i++)
    {
        for(int j = 0; j < (int)map_grid[i].size(); j++)
        {
            Entity quad = scene->CreateEntity();
            glm::vec3 scale = {TILE_SIZE, TILE_SIZE, 1.0f};
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, start_position);
            model = glm::scale(model, scale);
            quad.AddComponent<CoTransform>(model);
            quad.AddComponent<CoSprite>(map_grid[i][j] == TileType::OBSTACLE ? glm::vec4{0.0f, 0.0f, 0.0f, 1.0f} : glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
            quad.AddComponent<CoMapTile>(i,j);
            if(map_grid[i][j] == TileType::OBSTACLE)
            {
                quad.AddComponent<CoCollider>(glm::ivec2(TILE_SIZE + 1, TILE_SIZE + 1), true);
            }
            start_position += glm::vec3(TILE_SIZE, 0, 0);
        }
        start_position += glm::vec3(-start_position.x, TILE_SIZE, 0);
    }
}

void Map::RunCycle()
{
    Cycle();

    auto view = m_Scene->View<CoSprite, CoMapTile, CoCollider>();

    for (auto [entity, sprite, tile_cords, collider] : view.each())
    {
        sprite.color = map_grid[tile_cords.x][tile_cords.y] == TileType::OBSTACLE
            ? glm::vec4{0,0,0,1}
            : glm::vec4{1,1,1,1};
    }
}

void Map::Cycle()
{
    std::uniform_real_distribution<> dist(0.0f,1.0f);
    for(int y = 1; y < GRID_DIMENSIONS.y - 1; y++)
    {
        for(int x = 1; x < GRID_DIMENSIONS.x - 1; x++)
        {
            map_grid[y][x] = dist(rng) > wall_chance ? TileType::NONOBSTACLE : TileType::OBSTACLE;
        }
    } 
    for(int i = 0; i < CASTLE_SIZE; i++)
    {
        for(int j = 0; j < CASTLE_SIZE; j++)
        {
            map_grid[GRID_DIMENSIONS.y/2 - CASTLE_SIZE/2 + i][GRID_DIMENSIONS.x/2 - CASTLE_SIZE/2 + j] = TileType::SPECIAL; // means special
        }   
    }

    for(int i = 0; i < iterations; i++)
    {
        for(int y = 1; y < GRID_DIMENSIONS.y - 1; y++)
        {
            for(int x = 1; x < GRID_DIMENSIONS.x - 1; x++)
            {
                if(map_grid[y][x] == TileType::SPECIAL) continue;
                if(!Survival(y,x))
                {
                    map_grid[y][x] = TileType::NONOBSTACLE;
                }
                else if(Birth(y, x))
                {
                    map_grid[y][x] = TileType::OBSTACLE;
                }
            }
        } 
    }

    for(int i = 0; i < iterations; i++)
    {
        auto next_grid = map_grid; // copy current state

        for(int y = 1; y < GRID_DIMENSIONS.y - 1; y++)
        {
            for(int x = 1; x < GRID_DIMENSIONS.x - 1; x++)
            {
                if(map_grid[y][x] == TileType::SPECIAL) continue;

                if(!Survival(y,x))
                    next_grid[y][x] = TileType::NONOBSTACLE;
                else if(Birth(y, x))
                    next_grid[y][x] = TileType::OBSTACLE;
            }
        }

        map_grid = next_grid; // replace after whole step finished
    }
}