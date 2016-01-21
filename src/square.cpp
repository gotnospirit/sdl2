#include "square.h"
#include "utils.h"

Square::Square(int length) :
    DisplayObject()
{
    width = length;
    height = length;
}

Square::Square(int length, SDL_Color const &color) :
    DisplayObject(),
    color(color)
{
    width = length;
    height = length;
}

void Square::update(int)
{
}

void Square::render(SDL_Renderer * renderer)
{
    SDL_Rect r { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &r);
}
