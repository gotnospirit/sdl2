#include "display_object.h"
#include "utils.h"

DisplayObject::DisplayObject() :
    rect({ 0, 0, 0, 0 }),
    red(0),
    green(0),
    blue(0),
    alpha(100),
    clipping({ 0, 0, 0, 0 })
{
}

DisplayObject::~DisplayObject()
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
    rect.x = (container_width - width()) / 2;
    rect.y = (container_height - height()) / 2;
}

void DisplayObject::x(int value)
{
    rect.x = value;
}

void DisplayObject::y(int value)
{
    rect.y = value;
}

void DisplayObject::opacity(uint8_t value)
{
    alpha = clamp(value, 0, 100);
}

void DisplayObject::color(uint8_t r, uint8_t g, uint8_t b)
{
    red = r;
    green = g;
    blue = b;
}

int DisplayObject::x() const
{
    return rect.x;
}

int DisplayObject::y() const
{
    return rect.y;
}

int DisplayObject::width() const
{
    return clipping.w ? clipping.w : rect.w;
}

int DisplayObject::height() const
{
    return clipping.h ? clipping.h : rect.h;
}

bool DisplayObject::clipped() const
{
    return 0 != clipping.w || 0 != clipping.h || 0 != clipping.x || 0 != clipping.y;
}

