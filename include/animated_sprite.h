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

protected:
    int current_time;
    int duration;
    int current_frame;
    int max_frames;
    int clip_width;
    int clip_height;
    bool horizontal;
};

#endif // _ANIMATED_SPRITE_H_