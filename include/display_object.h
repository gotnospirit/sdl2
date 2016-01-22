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

    void clip(int, int, int, int);

    void center(int, int);

    void setX(int);
    void setY(int);
    void setAlpha(uint8_t); // percent
    void setColor(uint8_t, uint8_t, uint8_t);

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

protected:
    bool clipped() const;

    SDL_Point position;
    int width;
    int height;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_Rect clipping;
};

#endif // _DISPLAY_OBJECT_H_