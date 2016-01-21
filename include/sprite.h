#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>

class Sprite
{
public:
    Sprite();
    ~Sprite();

    bool load(const char *, SDL_Renderer *);

    void update(int);
    void render(SDL_Renderer *);

    void center(int, int);

protected:
    void free();

    SDL_Texture * texture = nullptr;
    SDL_Rect rect;
};

#endif // _SPRITE_H_