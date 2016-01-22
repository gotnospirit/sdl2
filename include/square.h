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
};

#endif // _SQUARE_H_