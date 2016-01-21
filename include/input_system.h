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
    SDL_Event e;
};

#endif // _INPUT_SYSTEM_H_