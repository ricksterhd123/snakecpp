#include "sdl.hpp"
#include "board.hpp"
#include "snake.hpp"
#include "food.hpp"

class Game
{
private:
    const int SCREEN_WIDTH = 300;
    const int SCREEN_HEIGHT = 300;
    const char *title = "snakecpp";
    const int SNAKE_SPEED = 5;
    const int FPS = SNAKE_SPEED;

    Window *window;
    Board *board;
    Snake *snake;
    Food *food;

    bool running;
    bool paused;
    Uint32 lastUpdateTick;

public:
    Game()
    {
        window = new Window(title, SCREEN_WIDTH, SCREEN_HEIGHT);
        board = new Board(SCREEN_WIDTH, SCREEN_HEIGHT);
        snake = new Snake(board, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, 0);
        food = new Food(board);

        lastUpdateTick = window->getTickCount();

        running = true;
        paused = false;
    }

    ~Game()
    {
        delete snake;
        delete board;
        delete window;
    }

    bool isRunning()
    {
        return running && !snake->getDied();
    }

    void setRunning(bool running)
    {
        this->running = running;
    }

    void update()
    {
        Uint32 currentTick = window->getTickCount();
        Vector2<int> snakeVelocity = snake->getVelocity();

        if (isRunning())
        {

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_LEFT && snakeVelocity.x <= 0)
                    {
                        snake->setVelocity(-1, 0);
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT && snakeVelocity.x >= 0)
                    {
                        snake->setVelocity(1, 0);
                    }
                    if (event.key.keysym.sym == SDLK_UP && snakeVelocity.y <= 0)
                    {
                        snake->setVelocity(0, -1);
                    }
                    if (event.key.keysym.sym == SDLK_DOWN && snakeVelocity.y >= 0)
                    {
                        snake->setVelocity(0, 1);
                    }
                    break;
                default:
                    break;
                }
            }

            snake->update(food);
            lastUpdateTick = window->getTickCount();
            SDL_Delay((1000 / FPS) - SDL_GetTicks() + lastUpdateTick);
        }
    }

    void draw()
    {
        board->draw(window);
        snake->draw(window);
        food->draw(window);
        window->draw();
    }

    void sleep(Uint32 ms)
    {
        SDL_Delay(ms);
    }
};
