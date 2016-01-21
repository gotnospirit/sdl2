#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <SDL.h>

class Square
{
public:
    Square(int);
    Square(int, SDL_Color const &);

    void x(int, int);
    void y(int, int);

    int x() const;
    int y() const;
    int length() const;

    void render(SDL_Renderer *);

private:
    SDL_Rect rect;
    SDL_Color color;
};

#endif // _SQUARE_H_