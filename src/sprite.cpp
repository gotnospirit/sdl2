#include <sstream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "sprite.h"

std::string getFilepath(const char * filename)
{
    std::ostringstream ss;
    ss << SDL_GetBasePath() << filename;
    return ss.str();
}

Sprite::Sprite()
{
}

Sprite::Sprite(const char * filename, SDL_Renderer * renderer)
{
    load(filename, renderer);
}

Sprite::~Sprite()
{
    free();
}

bool Sprite::load(const char * filename, SDL_Renderer * renderer)
{
    free();

    //Load image at specified path
    auto const &filepath = getFilepath(filename);

    printf("Loading '%s'\n", filepath.c_str());

    SDL_Surface * loadedSurface = IMG_Load(filepath.c_str());
    if (!loadedSurface)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filepath.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!texture)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
        }
        else
        {
            rect.w = loadedSurface->w;
            rect.h = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return !!texture;
}

void Sprite::render(SDL_Renderer * renderer)
{
    if (texture)
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}

void Sprite::free()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}
