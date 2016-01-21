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

void Actions::buttondown(SDL_ControllerButtonEvent const &e)
{
    switch (e.button)
    {
        case SDL_CONTROLLER_BUTTON_A: // cross
        case SDL_CONTROLLER_BUTTON_B: // circle
        case SDL_CONTROLLER_BUTTON_X: // square
        case SDL_CONTROLLER_BUTTON_Y: // triangle
        case SDL_CONTROLLER_BUTTON_BACK: // select
        case SDL_CONTROLLER_BUTTON_GUIDE: // PS
        case SDL_CONTROLLER_BUTTON_START: // start
        case SDL_CONTROLLER_BUTTON_LEFTSTICK: // L3
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK: // R3
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: // L1
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: // R1
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            data[ACTION_UP] = true;
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            data[ACTION_DOWN] = true;
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            data[ACTION_LEFT] = true;
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            data[ACTION_RIGHT] = true;
            break;
    }
}

void Actions::buttonup(SDL_ControllerButtonEvent const &e)
{
    switch (e.button)
    {
        case SDL_CONTROLLER_BUTTON_A: // cross
        case SDL_CONTROLLER_BUTTON_B: // circle
        case SDL_CONTROLLER_BUTTON_X: // square
        case SDL_CONTROLLER_BUTTON_Y: // triangle
        case SDL_CONTROLLER_BUTTON_BACK: // select
        case SDL_CONTROLLER_BUTTON_GUIDE: // PS
        case SDL_CONTROLLER_BUTTON_START: // start
        case SDL_CONTROLLER_BUTTON_LEFTSTICK: // L3
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK: // R3
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: // L1
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: // R1
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            data[ACTION_UP] = false;
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            data[ACTION_DOWN] = false;
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            data[ACTION_LEFT] = false;
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            data[ACTION_RIGHT] = false;
            break;
    }
}

bool Actions::enabled(int type) const
{
    return !!data[type];
}
