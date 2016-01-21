#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <SDL.h>

#include "display_object.h"

class Square :
    public DisplayObject
{
public:
    Square(int);
    Square(int, SDL_Color const &);

    void update(int);
    void render(SDL_Renderer *);

private:
    SDL_Color color;
};

#endif // _SQUARE_H_