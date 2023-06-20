#pragma once

#include "sdl.hpp"
#include "board.hpp"

class Food
{
private:
    const int vertexSize = 10;
    Board* board;
    Vector2<int> position;

public:
    Food(Board* board)
    {
        this->board = board;
        this->setRandomPosition();
    }

    Vector2<int> getPosition()
    {
        return position;
    }

    void setRandomPosition()
    {
        Vector2<int> boardSize = board->getSize();
        position = Vector2<int>(((rand() % boardSize.x) * vertexSize) % boardSize.x, ((rand() % boardSize.y) * vertexSize) % boardSize.y);
    }

    void draw(Window* window)
    {
        Vector2<int> boardSize = board->getSize();
        SDL_SetRenderDrawColor(window->getRenderer(), 0, 255, 0, 255);
        SDL_Rect point = {.x = (position.x), .y = (position.y), .w = vertexSize - 1, .h = vertexSize - 1};
        SDL_RenderFillRect(window->getRenderer(), &point);
    }
};
