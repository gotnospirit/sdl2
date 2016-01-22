#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <cstdint>

#include <SDL.h>

#include "display_object.h"

class Sprite :
    public DisplayObject
{
public:
    Sprite(SDL_Texture * = nullptr);
    ~Sprite();

    void update(int);
    void render(SDL_Renderer *);

    bool load(const char *, SDL_Renderer *);
    bool load(const char *, SDL_Renderer *, SDL_Color const &);

    void setAlpha(uint8_t); // percent
    void setColor(uint8_t, uint8_t, uint8_t);
    void setTexture(SDL_Texture *);

protected:
    SDL_Surface * loadSurface(const char *) const;
    SDL_Texture * loadTexture(SDL_Surface *, SDL_Renderer *) const;

    void applyAlpha();
    void free();

    SDL_Texture * texture = nullptr;
};

#endif // _SPRITE_H_