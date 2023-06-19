#include "game.hpp"

int main()
{
    Game* game = new Game();

    while (game->isRunning())
    {
        game->update();
        game->draw();
    }

    delete game;
    return 0;
}
