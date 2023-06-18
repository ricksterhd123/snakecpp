#include "snake.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* title = "snakecpp";

int main()
{
    Window window(title, SCREEN_HEIGHT, SCREEN_HEIGHT);
    Board board(SCREEN_WIDTH, SCREEN_HEIGHT);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }

        board.draw(window.getRenderer());
    }

    return 0;
}
