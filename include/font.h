#ifndef _FONT_H_
#define _FONT_H_

#include <cstdint>

#include <SDL.h>
#include <SDL_ttf.h>

class Font
{
public:
    ~Font();

    bool load(const char *, int);

    SDL_Texture * render(const char *, uint8_t, uint8_t, uint8_t, SDL_Renderer *, bool) const;
    SDL_Rect measure(const char *) const;

private:
    void free();

    TTF_Font * font = nullptr;
};

#endif // _FONT_H_