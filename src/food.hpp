#pragma once

#include <cstdlib>

#include "sdl.hpp"
#include "board.hpp"

class Food
{
private:
    const int spawnPadding = 30;
    const int vertexSize = 10;
    Board *board;
    Vector2<int> boardSize;
    Vector2<int> position;

public:
    Food(Board *board)
    {
        this->board = board;
        boardSize = board->getSize();
        setRandomPosition();
    }

    Vector2<int> getPosition()
    {
        return position;
    }

    void setRandomPosition()
    {
        position = Vector2<int>(
            clamp(((rand() % boardSize.x) * vertexSize) % boardSize.x, spawnPadding, boardSize.x - spawnPadding), 
            clamp(((rand() % boardSize.y) * vertexSize) % boardSize.y, spawnPadding, boardSize.y - spawnPadding));
    }

    void draw(Window *window)
    {
        SDL_SetRenderDrawColor(window->getRenderer(), 0, 0, 0, 255);
        SDL_Rect point = {.x = (position.x), .y = (position.y), .w = vertexSize - 1, .h = vertexSize - 1};
        SDL_RenderFillRect(window->getRenderer(), &point);
    }
};
