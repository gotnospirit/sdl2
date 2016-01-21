#include <iostream>

#include <SDL.h>

#include "input_system.h"

InputSystem::~InputSystem()
{
    if (gamepad)
    {
        SDL_GameControllerClose(gamepad);
    }
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

            case SDL_CONTROLLERDEVICEADDED:
                if (SDL_IsGameController(e.cdevice.which))
                {
                    if (gamepad)
                    {
                        std::cerr << "Too many gamepad..." << std::endl;
                    }
                    else
                    {
                        auto controller = SDL_GameControllerOpen(e.cdevice.which);

                        if (!controller)
                        {
                            std::cerr << "Could not open controller " << e.cdevice.which << ": " << SDL_GetError() << std::endl;
                        }
                        else if (SDL_GameControllerGetAttached(controller))
                        {
                            std::cout << "Controller <" << SDL_GameControllerName(controller) << "> added." << std::endl;
                            gamepad = controller;
                        }
                    }
                }
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                if (gamepad)
                {
                    SDL_GameControllerClose(gamepad);
                    gamepad = nullptr;
                    std::cout << "Controller <" << SDL_GameControllerName(gamepad) << "> removed." << std::endl;
                }
                break;

            case SDL_CONTROLLERBUTTONDOWN:
                actions->buttondown(e.cbutton);
                break;

            case SDL_CONTROLLERBUTTONUP:
                actions->buttonup(e.cbutton);
                break;
        }
    }
    return true;
}