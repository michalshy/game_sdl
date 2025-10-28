#include "game.h"
#include <memory>
#include "log.h"
Game::Game()
{
    level = std::make_unique<Level>();
}

bool Game::Init()
{
    if(!level->InitLevel())
        return false;

    LOG_DEBUG("Initialized Game");
    return true;
}