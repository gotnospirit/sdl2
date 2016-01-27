#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <cstdint>

#include <SDL.h>

#include "display_object.h"

class Square :
    public DisplayObject
{
public:
    Square();

    void update(int);
    void render(SDL_Renderer *);

    void size(int);
};

#endif // _SQUARE_H_