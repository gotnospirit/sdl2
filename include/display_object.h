#ifndef _DISPLAY_OBJECT_H_
#define _DISPLAY_OBJECT_H_

#include <cstdint>

#include <SDL.h>

class DisplayObject
{
public:
    DisplayObject();

    virtual void update(int) = 0;
    virtual void render(SDL_Renderer *) = 0;

    void center(int, int);

    void setX(int);
    void setY(int);
    void setAlpha(uint8_t); // percent

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

protected:
    int x;
    int y;
    int width;
    int height;
    uint8_t alpha;
};

#endif // _DISPLAY_OBJECT_H_