#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "sprite.h"
#include "utils.h"

Sprite::Sprite(SDL_Texture * ptr_texture) :
    DisplayObject(),
    rotation_deg(0.0),
    rotation_center({ 0, 0 }),
    has_rotation_center(false)
{
    setTexture(ptr_texture);
}

Sprite::~Sprite()
{
    free();
}

void Sprite::update(int)
{
}

void Sprite::render(SDL_Renderer * renderer)
{
    if (clipped())
    {
        SDL_Rect projection { rect.x, rect.y, clipping.w, clipping.h };
        render(renderer, &clipping, &projection);
    }
    else
    {
        render(renderer, NULL, &rect);
    }
}

bool Sprite::load(const char * filename, SDL_Renderer * renderer)
{
    SDL_Surface * surface = loadSurface(filename);
    if (surface)
    {
        setTexture(loadTexture(surface, renderer));
    }
    return !!texture;
}

bool Sprite::load(const char * filename, SDL_Renderer * renderer, SDL_Color const &transparency)
{
    SDL_Surface * surface = loadSurface(filename);
    if (surface)
    {
        //Color key image
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, transparency.r, transparency.g, transparency.b));

        setTexture(loadTexture(surface, renderer));
    }
    return !!texture;
}

void Sprite::rotate(double deg)
{
    rotation_deg = deg;
    has_rotation_center = false;
}

void Sprite::rotate(double deg, int x, int y)
{
    rotation_deg = deg;
    rotation_center.x = x;
    rotation_center.y = y;
    has_rotation_center = true;
}

void Sprite::opacity(uint8_t value)
{
    DisplayObject::opacity(value);
    applyAlpha();
}

void Sprite::color(uint8_t r, uint8_t g, uint8_t b)
{
    DisplayObject::color(r, g, b);

    if (texture)
    {
        SDL_SetTextureColorMod(texture, r, g, b);
    }
}

void Sprite::setTexture(SDL_Texture * ptr_texture)
{
    if (ptr_texture)
    {
        free();

        texture = ptr_texture;
        SDL_QueryTexture(ptr_texture, NULL, NULL, &rect.w, &rect.h);

        if (100 != alpha)
        {
            applyAlpha();
        }
    }
}

SDL_Surface * Sprite::loadSurface(const char * filename) const
{
    //Load image at specified path
    auto const &filepath = getFilepath(filename);

    std::cout << "Loading '" << filepath << "'" << std::endl;

    SDL_Surface * result = IMG_Load(filepath.c_str());
    if (!result)
    {
        std::cerr << "Unable to load image " << filepath << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    return result;
}

SDL_Texture * Sprite::loadTexture(SDL_Surface * surface, SDL_Renderer * renderer) const
{
    //Create texture from surface pixels
    SDL_Texture * result = SDL_CreateTextureFromSurface(renderer, surface);
    if (!result)
    {
        std::cerr << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
    }
    //Get rid of old loaded surface
    SDL_FreeSurface(surface);
    return result;
}

void Sprite::render(SDL_Renderer * renderer, SDL_Rect const * const src, SDL_Rect const * const dest)
{
    if (!renderer)
    {
        std::cerr << "Invalid renderer!" << std::endl;
        return ;
    }
    else if (!texture)
    {
        std::cerr << "No texture to render!" << std::endl;
        return ;
    }

    if (0.0 != rotation_deg)
    {
        SDL_RenderCopyEx(renderer, texture, src, dest, rotation_deg, has_rotation_center ? &rotation_center : NULL, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopy(renderer, texture, src, dest);
    }
}

void Sprite::applyAlpha()
{
    if (texture)
    {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
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
