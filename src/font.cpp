#include <iostream>

#include <SDL.h>

#include "font.h"
#include "utils.h"

Font::~Font()
{
    for (auto &pair : fonts)
    {
        TTF_CloseFont(pair.second);
    }
}

TTF_Font * Font::load(const char * filename, int ptsize)
{
    auto iter = fonts.find(filename);
    if (iter != fonts.end())
    {
        return iter->second;
    }

    auto const &filepath = getFilepath(filename);
    std::cout << "Loading '" << filepath << "'" << std::endl;

    auto result = TTF_OpenFont(filepath.c_str(), ptsize);
    if (!result)
    {
        std::cerr << "Failed to load font " << filepath << "! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    else
    {
        fonts.emplace(filename, result);
    }
    return result;
}

SDL_Texture * Font::render(const char * text, uint8_t r, uint8_t g, uint8_t b, const char * fontname, int fontsize, SDL_Renderer * renderer, bool high_res)
{
    SDL_Texture * result = nullptr;

    TTF_Font * font = load(fontname, fontsize);
    if (font)
    {
        //Render text surface
        SDL_Surface * surface = high_res
            ? TTF_RenderUTF8_Blended(font, text, { r, g, b })
            : TTF_RenderUTF8_Solid(font, text, { r, g, b });

        if (!surface)
        {
            std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        }
        else
        {
            //Create texture from surface pixels
            result = SDL_CreateTextureFromSurface(renderer, surface);
            if (!result)
            {
                std::cerr << "Unable to create texture from rendered text! SDL_ttf Error: " << TTF_GetError() << std::endl;
            }

            //Get rid of old surface
            SDL_FreeSurface(surface);
        }
    }
    return result;
}

SDL_Rect Font::measure(const char * text, const char * fontname, int fontsize)
{
    SDL_Rect result { 0, 0, 0, 0 };

    TTF_Font * font = load(fontname, fontsize);
    if (font)
    {
        if (TTF_SizeUTF8(font, text, &result.w, &result.h))
        {
            std::cerr << "Failed to measure '" << text << "'! SDL_ttf Error: " << TTF_GetError() << std::endl;
        }
    }
    return result;
}
