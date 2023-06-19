#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "sdl.hpp"

using namespace std;

class Board
{
private:
    Vector2<int> size;

public:
    Board(int width, int height)
    {
        size.x = width;
        size.y = height;
    }

    Vector2<int> getSize()
    {
        return size;
    }

    void draw(Window &window)
    {
    }
};

class Food
{
private:
    Vector2<int> position;

public:
    void draw(Window &window, Board &board)
    {
        Vector2<int> boardSize = board.getSize();
        SDL_SetRenderDrawColor(window.getRenderer(), 255, 0, 0, 255);
        SDL_Rect point = {.x = (position.x * 10) % boardSize.x, .y = (position.y * 10) % boardSize.y, .w = 9, .h = 9};
        SDL_RenderFillRect(window.getRenderer(), &point);
    }
};

class Snake
{
private:
    bool died;
    Vector2<int> vertexSize;
    Vector2<int> velocity;
    vector<Vector2<int>> vertices;

public:
    Snake(int x, int y, int vx, int vy)
    {
        // initial state
        died = false;

        vertexSize.x = 5;
        vertexSize.y = 5;

        // initial velocity
        velocity.x = vx;
        velocity.y = vy;

        // initial vertex
        vertices.insert(vertices.end(), Vector2<int>(x, y));
    }

    bool getDied()
    {
        return died;
    }

    void setDied(bool died)
    {
        this->died = died;
    }

    Vector2<int> getVelocity()
    {
        return velocity;
    }

    void setVelocity(int x, int y)
    {
        velocity.x = x;
        velocity.y = y;
    }

    void eat()
    {
        Vector2<int> first = vertices.at(0);
        Vector2<int> velocityNormalized = Vector2<int>(
            (velocity.x > 0) ? velocity.x / abs(velocity.x) : 0,
            (velocity.y > 0) ? (velocity.y / abs(velocity.y)) : 0);
        vertices.insert(vertices.begin(), first + velocityNormalized);
    }

    void update(Board &board)
    {
        Vector2<int> velocityNormalized = Vector2<int>(
            (velocity.x != 0) ? velocity.x / abs(velocity.x) : 0,
            (velocity.y != 0) ? (velocity.y / abs(velocity.y)) : 0);

        Vector2<int> newFirst = vertices.at(0) + velocityNormalized;

        for (std::vector<Vector2<int>>::iterator it = vertices.begin(); it < vertices.end(); it++)
        {
            if (*it == newFirst)
            {
                died = true;
                break;
            }
        }

        vertices.insert(vertices.begin(), newFirst);
        vertices.pop_back();
    }

    void draw(Window &window, Board &board)
    {
        Vector2<int> boardSize = board.getSize();
        for (std::vector<Vector2<int>>::iterator it = vertices.begin(); it < vertices.end(); it++)
        {
            SDL_SetRenderDrawColor(window.getRenderer(), 255, 0, 0, 255);
            SDL_Rect point = {.x = (it->x * 10) % boardSize.x, .y = (it->y * 10) % boardSize.y, .w = 9, .h = 9};
            SDL_RenderFillRect(window.getRenderer(), &point);
        }
    }
};

class Game
{
private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const char *title = "snakecpp";
    const int FPS = 1000 / 5;
    const int SNAKE_SPEED = 5;

    Window* window;
    Board* board;
    Snake* snake;
    Food* food;

    bool running;
    bool paused;
    Uint32 lastUpdateTick;

public:
    Game()
    {
        window = new Window(title, SCREEN_WIDTH, SCREEN_HEIGHT);
        board = new Board(SCREEN_WIDTH, SCREEN_HEIGHT);
        snake = new Snake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SNAKE_SPEED, 0);
        lastUpdateTick = window->getTickCount();

        running = true;
        paused = false;
    }

    ~Game() {
        delete snake;
        delete board;
        delete window;
    }

    bool isRunning() {
        return running && !snake->getDied();
    }

    void setRunning(bool running) {
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
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    snake->eat();
                }
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    // paused = !paused;
                }
                break;
            default:
                break;
            }
        }

        if (!paused && currentTick - lastUpdateTick > FPS)
        {
            snake->update(*board);
            lastUpdateTick = window->getTickCount();
        }
    }

    void draw()
    {
        snake->draw(*window, *board);
        // board.draw(window.getRenderer());
        window->draw();
    }
};
