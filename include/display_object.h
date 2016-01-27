#ifndef _DISPLAY_OBJECT_H_
#define _DISPLAY_OBJECT_H_

#include <cstdint>

#include <SDL.h>

class DisplayObject
{
public:
    DisplayObject();
    virtual ~DisplayObject();

    virtual void update(int) = 0;
    virtual void render(SDL_Renderer *) = 0;

    void clip(int, int, int, int);

    void center(int, int);

    void x(int);
    void y(int);
    void opacity(uint8_t); // percent
    void color(uint8_t, uint8_t, uint8_t);

    int x() const;
    int y() const;
    int width() const;
    int height() const;

protected:
    bool clipped() const;

    SDL_Rect rect;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_Rect clipping;
};

#endif // _DISPLAY_OBJECT_H_