#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <cstdint>

#include <SDL.h>

#include "display_object.h"

class Sprite :
    public DisplayObject
{
public:
    ~Sprite();

    void update(int);
    void render(SDL_Renderer *);

    bool load(const char *, SDL_Renderer *);

    void setAlpha(uint8_t); // percent

protected:
    void applyAlpha();
    void free();

    SDL_Texture * texture = nullptr;
};

#endif // _SPRITE_H_