#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>

class Sprite
{
public:
    Sprite();
    Sprite(const char *, SDL_Renderer *);
    ~Sprite();

    bool load(const char *, SDL_Renderer *);

    void render(SDL_Renderer *);

private:
    void free();

    SDL_Texture * texture = nullptr;
    SDL_Rect rect;
};

#endif // _SPRITE_H_