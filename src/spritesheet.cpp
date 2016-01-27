#include "spritesheet.h"
#include "utils.h"

Spritesheet::Spritesheet() :
    Sprite(),
    current_time(0),
    max_time(0),
    current_frame(0),
    max_frames(0),
    horizontal(false)
{
}

void Spritesheet::update(int delta)
{
    Sprite::update(delta);

    current_time += delta;
    if (current_time > max_time)
    {
        current_time = 0;
    }

    current_frame = (int)(max_frames * linearEaseIn(current_time, 0, 1, max_time));
}

void Spritesheet::render(SDL_Renderer * renderer)
{
    if (horizontal)
    {
        clipping.x = current_frame * clipping.w;
        clipping.y = 0;
    }
    else
    {
        clipping.x = 0;
        clipping.y = current_frame * clipping.h;
    }

    Sprite::render(renderer);
}

void Spritesheet::duration(int value)
{
    max_time = value > 0 ? value : 0;
}

void Spritesheet::clip(int x, int y, int w, int h)
{
    max_frames = (rect.w / w) >> 0;

    Sprite::clip(x, y, w, h);
}

void Spritesheet::orientation(bool vertical)
{
    horizontal = !vertical;
}
