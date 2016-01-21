#include <SDL.h>

#include "actions.h"

Actions::Actions()
{
    data[ACTION_UP] = false;
    data[ACTION_DOWN] = false;
    data[ACTION_LEFT] = false;
    data[ACTION_RIGHT] = false;
}

void Actions::keydown(SDL_Event const &e)
{
    switch (e.key.keysym.sym)
    {
        case SDLK_UP:
            data[ACTION_UP] = true;
            break;

        case SDLK_DOWN:
            data[ACTION_DOWN] = true;
            break;

        case SDLK_LEFT:
            data[ACTION_LEFT] = true;
            break;

        case SDLK_RIGHT:
            data[ACTION_RIGHT] = true;
            break;
    }
}

void Actions::keyup(SDL_Event const &e)
{
    switch (e.key.keysym.sym)
    {
        case SDLK_UP:
            data[ACTION_UP] = false;
            break;

        case SDLK_DOWN:
            data[ACTION_DOWN] = false;
            break;

        case SDLK_LEFT:
            data[ACTION_LEFT] = false;
            break;

        case SDLK_RIGHT:
            data[ACTION_RIGHT] = false;
            break;
    }
}

bool Actions::enabled(int type) const
{
    return !!data[type];
}
