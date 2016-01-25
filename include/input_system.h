#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include <SDL.h>

#include "actions.h"
#include "system.h"
#include "message_bus.h"

class InputSystem :
    public System
{
public:
    InputSystem(MessageBus *);
    ~InputSystem();

    void handleMessage(const char *, size_t);

    bool poll();

private:
    void keyup(SDL_Event const &);
    void keydown(SDL_Event const &);

    void buttonup(SDL_ControllerButtonEvent const &);
    void buttondown(SDL_ControllerButtonEvent const &);

    SDL_Event e;
    Actions actions;

    unsigned long update_time = 0;

    SDL_GameController * gamepad = nullptr;
};

#endif // _INPUT_SYSTEM_H_