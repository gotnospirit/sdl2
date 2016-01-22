#include "square.h"
#include "utils.h"

Square::Square(int length) :
    DisplayObject(),
    r(0),
    g(0),
    b(0)
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
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect rect { x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}

void Square::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    this->r = clamp(r, 0, 255);
    this->g = clamp(g, 0, 255);
    this->b = clamp(b, 0, 255);
}
