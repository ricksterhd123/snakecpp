#pragma once

#include <iostream>
#include <exception>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

template <class N>
N clamp(N n, N a, N b)
{
    if (n < a) {
        return a;
    } else if (n > b) {
        return b;
    }

    return n;
}

template <class N>
class Vector2
{
public:
    N x;
    N y;

    Vector2()
    {
        this->x = 0;
        this->y = 0;
    }

    Vector2(N x, N y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2 operator+(Vector2 rVector)
    {
        return Vector2(
            this->x + rVector.x,
            this->y + rVector.y);
    }

    Vector2 operator-(Vector2 rVector)
    {
        return *this + Vector2(-rVector.x, -rVector.y);
    }

    Vector2 operator%(const Vector2 rVector)
    {
        return Vector2(this->x % rVector.x, this->y % rVector.y);
    }

    Vector2 operator*(int rNum)
    {
        return Vector2(this->x * rNum, this->y * rNum);
    }

    bool operator==(const Vector2 rVector)
    {
        return this->x == rVector.x && this->y == rVector.y;
    }

    bool operator!=(const Vector2 rVector)
    {
        return this->x != rVector.x || this->y != rVector.y;
    }
};

template <class N>
std::ostream &operator<<(std::ostream &os, const Vector2<N> &obj)
{
    os << "{x=" << obj.x << ", y=" << obj.y << "}";
    return os;
}

class SDLError : public std::exception
{
private:
    char *message;

public:
    SDLError()
    {
        const char *tmp = SDL_GetError();
        message = (char *)malloc(strlen(tmp) + 1);
        strcpy(message, tmp);
    }

    char *what()
    {
        return message;
    }

    ~SDLError()
    {
        free(message);
    }
};

// class Text
// {
//     private:
//         TTF_Font font;
// };

class Window
{
private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

public:
    Window(const char *title, int width, int height)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
        {
            throw SDLError();
        }

        window = SDL_CreateWindow(
            title, // window title
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,  // width, in pixels
            height, // height, in pixels
            SDL_WINDOW_OPENGL);

        if (window == NULL)
        {
            throw SDLError();
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
        {
            throw SDLError();
        }
    }

    ~Window()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    Uint32 getTickCount()
    {
        return SDL_GetTicks();
    }

    SDL_Renderer *getRenderer()
    {
        return renderer;
    }

    SDL_Window *getWindow()
    {
        return window;
    }

    void draw()
    {
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
};
