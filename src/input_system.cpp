#include <iostream>

#include <SDL.h>

#include "input_system.h"

InputSystem::~InputSystem()
{
}

bool InputSystem::poll(Actions * actions)
{
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
            case SDL_QUIT:
                return false;

            case SDL_KEYDOWN:
                actions->keydown(e);
                break;

            case SDL_KEYUP:
                actions->keyup(e);
                break;
        }
    }
    return true;
}