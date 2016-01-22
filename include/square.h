#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <cstdint>

#include <SDL.h>

#include "display_object.h"

class Square :
    public DisplayObject
{
public:
    Square(int);

    void update(int);
    void render(SDL_Renderer *);

    void setColor(uint8_t, uint8_t, uint8_t);

private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

#endif // _SQUARE_H_