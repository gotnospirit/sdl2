#include "square.h"
#include "utils.h"

Square::Square() :
    DisplayObject()
{
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

    if (clipped())
    {
        SDL_Rect projection { rect.x, rect.y, clipping.w, clipping.h };
        SDL_RenderFillRect(renderer, &projection);
    }
    else
    {
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Square::size(int length)
{
    rect.w = length;
    rect.h = length;
}