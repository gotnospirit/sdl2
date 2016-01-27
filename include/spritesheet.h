#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include <SDL.h>

#include "sprite.h"

class Spritesheet :
    public Sprite
{
public:
    Spritesheet();

    void update(int);
    void render(SDL_Renderer *);

    void duration(int);

    void clip(int, int, int, int);
    void orientation(bool);

protected:
    int current_time;
    int max_time;
    int current_frame;
    int max_frames;
    bool horizontal;
};

#endif // _SPRITESHEET_H_