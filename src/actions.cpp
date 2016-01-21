#include "actions.h"

Actions::Actions()
{
    data[ACTION_UP] = false;
    data[ACTION_DOWN] = false;
    data[ACTION_LEFT] = false;
    data[ACTION_RIGHT] = false;
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
