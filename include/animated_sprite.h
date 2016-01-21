#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_

#include <SDL.h>

#include "sprite.h"

class AnimatedSprite :
    public Sprite
{
public:
    AnimatedSprite(int);

    void update(int);
    void render(SDL_Renderer *);

    void clip(int, int, bool);

    void center(int, int);

protected:
    SDL_Rect clip_rect;
    int current;
    int duration;
    int max_frames;
    bool horizontal;
};

#endif // _ANIMATED_SPRITE_H_