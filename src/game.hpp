#include "sdl.hpp"
#include "board.hpp"
#include "snake.hpp"
#include "food.hpp"

class Game
{
private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const char *title = "snakecpp";
    const int FPS = 1000 / 5;
    const int SNAKE_SPEED = 5;

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
        snake = new Snake(board, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SNAKE_SPEED, 0);
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
                    snake->setVelocity(-1 * SNAKE_SPEED, 0);
                }
                if (event.key.keysym.sym == SDLK_RIGHT && snakeVelocity.x >= 0)
                {
                    snake->setVelocity(1 * SNAKE_SPEED, 0);
                }
                if (event.key.keysym.sym == SDLK_UP && snakeVelocity.y <= 0)
                {
                    snake->setVelocity(0, -1 * SNAKE_SPEED);
                }
                if (event.key.keysym.sym == SDLK_DOWN && snakeVelocity.y >= 0)
                {
                    snake->setVelocity(0, 1 * SNAKE_SPEED);
                }
                break;
            default:
                break;
            }
        }

        if (!paused && currentTick - lastUpdateTick > FPS)
        {
            snake->update(food);
            lastUpdateTick = window->getTickCount();
        }
    }

    void draw()
    {
        snake->draw(window);
        food->draw(window);
        window->draw();
    }
};
