#define DEBUG 1

#include "game.hpp"
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

Game *game;

void main_loop()
{
    game->update();
    game->draw();
}

int main()
{
    game = new Game();

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (game->isRunning())
    {
        main_loop();
    }
#endif

    cout << "You died" << endl;

    game->sleep(5000);

    cout << "Cleaning up and quitting..." << endl;

    delete game;
    return 0;
}
