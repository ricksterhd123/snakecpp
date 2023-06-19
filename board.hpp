#pragma once

#include "sdl.hpp"

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
};
