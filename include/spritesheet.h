#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include <SDL.h>

#include "sprite.h"

class Spritesheet :
    public Sprite
{
public:
    Spritesheet(int);

    void update(int);
    void render(SDL_Renderer *);

    void clip(int, int, int, int);
    void orientation(bool);

protected:
    int current_time;
    int duration;
    int current_frame;
    int max_frames;
    bool horizontal;
};

#endif // _SPRITESHEET_H_