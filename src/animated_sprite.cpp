#include <SDL.h>

#include "animated_sprite.h"
#include "utils.h"

AnimatedSprite::AnimatedSprite(int duration) :
    current_time(0),
    duration(duration),
    current_frame(0),
    max_frames(0),
    horizontal(false)
{
    clip_width = 0;
    clip_height = 0;
}

void AnimatedSprite::update(int delta)
{
    Sprite::update(delta);

    current_time += delta;
    if (current_time > duration)
    {
        current_time = 0;
    }

    current_frame = max_frames * linearEaseIn(current_time, 0, 1, duration);
}

void AnimatedSprite::render(SDL_Renderer * renderer)
{
    if (texture)
    {
        SDL_Rect cr { 0, 0, clip_width, clip_height };

        if (horizontal)
        {
            cr.x = current_frame * clip_width;
        }
        else
        {
            cr.y = current_frame * clip_height;
        }

        SDL_Rect r { x, y, clip_width, clip_height };
        SDL_RenderCopy(renderer, texture, &cr, &r);
    }
    else
    {
        throw "No texture loaded!";
    }
}

void AnimatedSprite::clip(int w, int h, bool vertical)
{
    max_frames = (width / w) >> 0;
    horizontal = !vertical;

    clip_width = w;
    clip_height = h;

    width = w;
    height = h;
}
