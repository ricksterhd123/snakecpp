#pragma once

#include <vector>
#include <cstdlib>

#include "sdl.hpp"
#include "board.hpp"
#include "food.hpp"

using std::cout;
using std::endl;
using std::vector;

class Snake
{
private:
    const int vertexSize = 10;
    const int initialSize = 5;

    bool died;
    Board *board;
    Vector2<int> boardSize;
    Vector2<int> velocity;
    vector<Vector2<int>> vertices;

public:
    Snake(Board *board, int x, int y, int vx, int vy)
    {
        this->board = board;
        boardSize = board->getSize();

        // initial state
        died = false;

        // initial velocity
        velocity.x = vx;
        velocity.y = vy;

        // initial vertex
        for (int i = 0; i < initialSize; i++)
        {
            vertices.insert(vertices.end(), Vector2<int>(x, y) + (velocity * i));
        }
    }

    bool isOutOfBounds()
    {
        return board->isOutOfBounds(vertices.at(0));
    }

    bool getDied()
    {
        return isOutOfBounds() || died;
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
        vertices.insert(vertices.begin(), first + velocity);
    }

    void update(Food *food)
    {

        int speed = floor(sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)));
        Vector2<int> newFirst = (vertices.at(0) + (velocity * vertexSize));
        Vector2<int> foodPos = food->getPosition();

#ifdef DEBUG
        cout << newFirst << endl;
#endif

        if (newFirst == food->getPosition())
        {
            this->eat();
            food->setRandomPosition();
        }

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

    void draw(Window *window)
    {
        for (std::vector<Vector2<int>>::iterator it = vertices.begin(); it < vertices.end(); it++)
        {
            SDL_SetRenderDrawColor(window->getRenderer(), 0, 0, 0, 255);
            SDL_Rect point = {.x = (it->x), .y = (it->y), .w = vertexSize - 1, .h = vertexSize - 1};
            SDL_RenderFillRect(window->getRenderer(), &point);
        }
    }
};
