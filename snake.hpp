#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

using namespace std;

struct Vector2
{
    int x;
    int y;
};

class Snake
{
private:
    vector<Vector2> points;

public:
    Snake()
    {
    }
};

class Board
{
private:
    int width;
    int height;

public:
    Board(int width, int height)
    {
        cout << width << height << endl;
    }

    int getWidth()
    {
        return this->width;
    }

    int getHeight()
    {
        return this->height;
    }

    void draw(SDL_Renderer *renderer)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
};

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

        this->window = SDL_CreateWindow(
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

        this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
        {
            throw SDLError();
        }
    }

    ~Window()
    {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    SDL_Renderer *getRenderer()
    {
        return this->renderer;
    }

    SDL_Window *getWindow()
    {
        return this->window;
    }

    void 
};
