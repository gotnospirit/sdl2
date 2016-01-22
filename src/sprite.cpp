#include <SDL.h>
#include <SDL_image.h>

#include "sprite.h"
#include "utils.h"

Sprite::~Sprite()
{
    free();
}

void Sprite::update(int)
{
}

void Sprite::render(SDL_Renderer * renderer)
{
    if (texture)
    {
        SDL_Rect r { x, y, width, height };
        SDL_RenderCopy(renderer, texture, NULL, &r);
    }
    else
    {
        throw "No texture loaded!";
    }
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
            width = loadedSurface->w;
            height = loadedSurface->h;
            applyAlpha();
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return !!texture;
}

void Sprite::setAlpha(uint8_t value)
{
    DisplayObject::setAlpha(value);
    applyAlpha();
}

void Sprite::applyAlpha()
{
    if (texture)
    {
        SDL_SetTextureAlphaMod(texture, (uint8_t)(alpha * 255 / 100));
    }
}

void Sprite::free()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
