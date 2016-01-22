#include "display_object.h"
#include "utils.h"

DisplayObject::DisplayObject() :
    x(0),
    y(0),
    width(0),
    height(0),
    red(0),
    green(0),
    blue(0),
    alpha(100),
    clipping({ 0, 0, 0, 0 })
{
}

void DisplayObject::clip(int x, int y, int w, int h)
{
    clipping.x = x;
    clipping.y = y;
    clipping.w = w;
    clipping.h = h;
}

void DisplayObject::center(int container_width, int container_height)
{
    int w = clipping.w ? clipping.w : width;
    int h = clipping.h ? clipping.h : height;
    x = (container_width - w) / 2;
    y = (container_height - h) / 2;
}

void DisplayObject::setX(int value)
{
    x = value;
}

void DisplayObject::setY(int value)
{
    y = value;
}

void DisplayObject::setAlpha(uint8_t value)
{
    alpha = clamp(value, 0, 100);
}

void DisplayObject::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    red = r;
    green = g;
    blue = b;
}

int DisplayObject::getX() const
{
    return x;
}

int DisplayObject::getY() const
{
    return y;
}

int DisplayObject::getWidth() const
{
    return clipping.w ? clipping.w : width;
}

int DisplayObject::getHeight() const
{
    return clipping.h ? clipping.h : height;
}

bool DisplayObject::clipped() const
{
    return 0 != clipping.w || 0 != clipping.h || 0 != clipping.x || 0 != clipping.y;
}

