#include "game.hpp"

int main()
{
    Game* game = new Game();

    while (game->isRunning())
    {
        game->update();
        game->draw();
    }

    cout << "You died" << endl;

    game->sleep(5000);

    cout << "Cleaning up and quitting..." << endl;

    delete game;
    return 0;
}
