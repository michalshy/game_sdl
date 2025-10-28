#pragma once
#include "level/level.h"
#include <memory>

class Game
{
    std::unique_ptr<Level> level;
public:
    Game();
    bool Init();
};