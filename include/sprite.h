#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>

#include "display_object.h"

class Sprite :
    public DisplayObject
{
public:
    ~Sprite();

    bool load(const char *, SDL_Renderer *);

    void update(int);
    void render(SDL_Renderer *);

protected:
    void free();

    SDL_Texture * texture = nullptr;
};

#endif // _SPRITE_H_