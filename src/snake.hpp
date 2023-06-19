#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "sdl.hpp"
#include "board.hpp"
#include "food.hpp"

using namespace std;

class Snake
{
private:
    bool died;
    Board* board;
    Vector2<int> vertexSize;
    Vector2<int> velocity;
    vector<Vector2<int>> vertices;

public:
    Snake(Board* board, int x, int y, int vx, int vy)
    {
        this->board = board;

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

    void update(Food* food)
    {
        Vector2<int> velocityNormalized = Vector2<int>(
            (velocity.x != 0) ? velocity.x / abs(velocity.x) : 0,
            (velocity.y != 0) ? (velocity.y / abs(velocity.y)) : 0);

        Vector2<int> newFirst = (vertices.at(0) + velocityNormalized * 10) % board->getSize();
        Vector2<int> foodPos = food->getPosition();

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

    void draw(Window* window)
    {
        Vector2<int> boardSize = board->getSize();
        for (std::vector<Vector2<int>>::iterator it = vertices.begin(); it < vertices.end(); it++)
        {
            SDL_SetRenderDrawColor(window->getRenderer(), 255, 0, 0, 255);
            SDL_Rect point = {.x = (it->x), .y = (it->y), .w = 9, .h = 9};
            SDL_RenderFillRect(window->getRenderer(), &point);
        }
    }
};
