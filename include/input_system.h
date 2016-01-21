#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include <SDL.h>

#include "actions.h"

class InputSystem
{
public:
    ~InputSystem();

    bool poll(Actions *);

private:
    void keyup(Actions *, SDL_Event const &);
    void keydown(Actions *, SDL_Event const &);

    void buttonup(Actions *, SDL_ControllerButtonEvent const &);
    void buttondown(Actions *, SDL_ControllerButtonEvent const &);

    SDL_Event e;
    SDL_GameController * gamepad = nullptr;
};

#endif // _INPUT_SYSTEM_H_