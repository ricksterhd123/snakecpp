#pragma once

#include "sdl.hpp"

class Board
{
private:
    const int margin = 10;
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

    bool isOutOfBounds(Vector2<int> position)
    {
        return position.x <= margin ||
               position.x >= size.x - margin ||
               position.y <= margin ||
               position.y >= size.y - margin;
    }

    void draw(Window *window)
    {
        SDL_SetRenderDrawColor(window->getRenderer(), 137, 226, 0, 255);
        SDL_Rect background = {.x = 0, .y = 0, .w = size.x, .h = size.y};
        SDL_RenderFillRect(window->getRenderer(), &background);

        SDL_SetRenderDrawColor(window->getRenderer(), 38, 38, 38, 255);
        SDL_Rect top = {.x = 0, .y = 0, .w = size.x, .h = margin};
        SDL_Rect bottom = {.x = 0, .y = size.y - margin, .w = size.x, .h = margin};
        SDL_Rect left = {.x = 0, .y = 0, .w = margin, .h = size.y};
        SDL_Rect right = {.x = size.y - margin, .y = 0, .w = margin, .h = size.y};
        SDL_RenderFillRect(window->getRenderer(), &top);
        SDL_RenderFillRect(window->getRenderer(), &bottom);
        SDL_RenderFillRect(window->getRenderer(), &left);
        SDL_RenderFillRect(window->getRenderer(), &right);
    }
};
