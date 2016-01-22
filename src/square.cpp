#include "square.h"
#include "utils.h"

Square::Square(int length) :
    DisplayObject()
{
    width = length;
    height = length;
}

void Square::update(int)
{
}

void Square::render(SDL_Renderer * renderer)
{
    uint8_t a = 255;
    if (100 != alpha)
    {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        a = alpha * 255 / 100;
    }
    SDL_SetRenderDrawColor(renderer, red, green, blue, a);

    SDL_Rect projection { x, y, width, height };
    if (clipped())
    {
        projection.w = clipping.w;
        projection.h = clipping.h;
    }
    SDL_RenderFillRect(renderer, &projection);
}
