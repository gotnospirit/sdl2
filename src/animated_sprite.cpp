#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "animated_sprite.h"

float linearEaseIn(float t, float b, float c, float d)
{
    return c * t / d + b;
}

AnimatedSprite::AnimatedSprite(int duration) :
    current(0),
    duration(duration),
    max_frames(0),
    horizontal(false)
{
    clip_rect.x = 0;
    clip_rect.y = 0;
    clip_rect.w = 0;
    clip_rect.h = 0;
}

void AnimatedSprite::update(int delta)
{
    Sprite::update(delta);

    current += delta;
    if (current > duration)
    {
        current = 0;
    }

    int n = max_frames * linearEaseIn(current, 0, 1, duration);

    if (horizontal)
    {
        clip_rect.x = n * clip_rect.w;
        clip_rect.y = 0;
    }
    else
    {
        clip_rect.x = 0;
        clip_rect.y = n * clip_rect.h;
    }
}

void AnimatedSprite::render(SDL_Renderer * renderer)
{
    if (texture)
    {
        SDL_Rect r { rect.x, rect.y, clip_rect.w, clip_rect.h };
        SDL_RenderCopy(renderer, texture, &clip_rect, &r);
    }
    else
    {
        throw "No texture loaded!";
    }
}

void AnimatedSprite::clip(int w, int h, bool vertical)
{
    if (texture)
    {
        max_frames = (rect.w / w) >> 0;
        horizontal = !vertical;

        clip_rect.x = 0;
        clip_rect.y = 0;
        clip_rect.w = w;
        clip_rect.h = h;
    }
    else
    {
        throw "No texture loaded!";
    }
}

void AnimatedSprite::center(int w, int h)
{
    if (texture)
    {
        rect.x = (w - clip_rect.w) / 2;
        rect.y = (h - clip_rect.h) / 2;
    }
    else
    {
        throw "No texture loaded!";
    }
}
