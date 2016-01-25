#include "actions.h"

Actions::Actions()
{
    for (auto i = 0; i < ACTION_COUNT; ++i)
    {
        data[i] = false;
    }
}

void Actions::moveUp(bool enabled)
{
    data[ACTION_UP] = enabled;
}

void Actions::moveDown(bool enabled)
{
    data[ACTION_DOWN] = enabled;
}

void Actions::moveLeft(bool enabled)
{
    data[ACTION_LEFT] = enabled;
}

void Actions::moveRight(bool enabled)
{
    data[ACTION_RIGHT] = enabled;
}

bool Actions::enabled(int type) const
{
    return !!data[type];
}
