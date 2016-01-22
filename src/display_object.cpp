#include "display_object.h"
#include "utils.h"

DisplayObject::DisplayObject() :
    x(0),
    y(0),
    width(0),
    height(0),
    alpha(100)
{
}

void DisplayObject::center(int container_width, int container_height)
{
    x = (container_width - width) / 2;
    y = (container_height - height) / 2;
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
    return width;
}

int DisplayObject::getHeight() const
{
    return height;
}
