#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include <SDL.h>

#include "system.h"
#include "message_bus.h"
#include "actions.h"

class InputSystem :
    public System
{
public:
    InputSystem(MessageBus *);
    ~InputSystem();

    void handleMessage(Message const &);

    bool poll();

private:
    void keyup(SDL_Event const &);
    void keydown(SDL_Event const &);

    void buttonup(SDL_ControllerButtonEvent const &);
    void buttondown(SDL_ControllerButtonEvent const &);

    SDL_Event e;
    SDL_Point cursor;
    bool cursor_moved;
    Actions actions;

    unsigned long update_time = 0;

    SDL_GameController * gamepad = nullptr;
};

#endif // _INPUT_SYSTEM_H_