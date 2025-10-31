#include "gameplay/game.h"

int main(int, char*[]) {

    Game game;
    if(!game.Init())
        return 1;

    game.Run();
    return 0;
}