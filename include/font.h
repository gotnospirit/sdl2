#ifndef _FONT_H_
#define _FONT_H_

#include <cstdint>
#include <unordered_map>

#include <SDL.h>
#include <SDL_ttf.h>

class Font
{
public:
    ~Font();

    SDL_Texture * render(const char *, uint8_t, uint8_t, uint8_t, const char *, int, SDL_Renderer *, bool);
    SDL_Rect measure(const char *, const char *, int);

private:
    TTF_Font * load(const char *, int);

    std::unordered_map<std::string, TTF_Font *> fonts;
};

#endif // _FONT_H_