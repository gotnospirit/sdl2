#include "square.h"

int clamp(int value, int min, int max)
{
    if (value > max)
    {
        return max;
    }
    else if (value < min)
    {
        return min;
    }
    return value;
}

Square::Square(int length)
{
    rect.x = 0;
    rect.y = 0;
    rect.w = length;
    rect.h = length;
}

Square::Square(int length, SDL_Color const &color) :
    color(color)
{
    rect.x = 0;
    rect.y = 0;
    rect.w = length;
    rect.h = length;
}

void Square::x(int value, int max)
{
    rect.x = clamp(value, 0, max);
}

void Square::y(int value, int max)
{
    rect.y = clamp(value, 0, max);
}

int Square::x() const
{
    return rect.x;
}

int Square::y() const
{
    return rect.y;
}

int Square::length() const
{
    return rect.w;
}

void Square::center(int w, int h)
{
    rect.x = (w - rect.w) / 2;
    rect.y = (h - rect.h) / 2;
}

void Square::render(SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}
