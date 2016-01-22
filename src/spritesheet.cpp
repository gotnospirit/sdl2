#include <SDL.h>

#include "spritesheet.h"
#include "utils.h"

Spritesheet::Spritesheet(int duration) :
    current_time(0),
    duration(duration),
    current_frame(0),
    max_frames(0),
    horizontal(false)
{
}

void Spritesheet::update(int delta)
{
    Sprite::update(delta);

    current_time += delta;
    if (current_time > duration)
    {
        current_time = 0;
    }

    current_frame = (int)(max_frames * linearEaseIn(current_time, 0, 1, duration));
}

void Spritesheet::render(SDL_Renderer * renderer)
{
    if (texture)
    {
        SDL_Rect cr { 0, 0, width, height };

        if (horizontal)
        {
            cr.x = current_frame * width;
        }
        else
        {
            cr.y = current_frame * height;
        }

        SDL_Rect r { x, y, width, height };
        SDL_RenderCopy(renderer, texture, &cr, &r);
    }
    else
    {
        throw "No texture loaded!";
    }
}

void Spritesheet::clip(int w, int h, bool vertical)
{
    max_frames = (width / w) >> 0;
    horizontal = !vertical;

    width = w;
    height = h;
}
