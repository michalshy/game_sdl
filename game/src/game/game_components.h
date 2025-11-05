#pragma once

enum class TileType
{
    NONOBSTACLE,
    OBSTACLE,
    SPECIAL,
};

struct CoMapTile
{
    int x;
    int y;
};