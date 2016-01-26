#include <iostream>
#include <sstream>
#include <cstring>

#include <SDL.h>

#include "input_system.h"

InputSystem::InputSystem(MessageBus * bus) :
    System(bus)
{
}

InputSystem::~InputSystem()
{
    if (gamepad)
    {
        SDL_GameControllerClose(gamepad);
    }
}

void InputSystem::handleMessage(const char * msg, size_t msglen)
{
    if (0 == strncmp(msg, "TICK ", 5) && msglen > 5)
    {
        unsigned long frame_time = atoi(msg + 5);

        //Update models logic (200Hz)
        if ((frame_time - update_time) >= 5)
        {
            update_time = frame_time;

            sendMessage("COUNTER UPDATE");

            if (actions.enabled(ACTION_UP))
            {
                sendMessage("MOVE UP");
            }

            if (actions.enabled(ACTION_DOWN))
            {
                sendMessage("MOVE DOWN");
            }

            if (actions.enabled(ACTION_LEFT))
            {
                sendMessage("MOVE LEFT");
            }

            if (actions.enabled(ACTION_RIGHT))
            {
                sendMessage("MOVE RIGHT");
            }
        }
    }
}

bool InputSystem::poll()
{
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
            case SDL_QUIT:
                return false;

            case SDL_KEYDOWN:
                keydown(e);
                break;

            case SDL_KEYUP:
                keyup(e);
                break;

            case SDL_CONTROLLERDEVICEADDED:
                if (SDL_IsGameController(e.cdevice.which))
                {
                    if (gamepad)
                    {
                        std::cerr << "Too many game controller..." << std::endl;
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
                            std::cout << "Controller <" << SDL_GameControllerName(controller) << "> added" << std::endl;
                            gamepad = controller;
                        }
                    }
                }
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                if (gamepad)
                {
                    std::cout << "Removing controller <" << SDL_GameControllerName(gamepad) << ">" << std::endl;
                    SDL_GameControllerClose(gamepad);
                    gamepad = nullptr;
                }
                break;

            case SDL_CONTROLLERBUTTONDOWN:
                buttondown(e.cbutton);
                break;

            case SDL_CONTROLLERBUTTONUP:
                buttonup(e.cbutton);
                break;
        }
    }
    return true;
}

void InputSystem::keyup(SDL_Event const &e)
{
    switch (e.key.keysym.sym)
    {
        case SDLK_UP:
            actions.moveUp(false);
            break;

        case SDLK_DOWN:
            actions.moveDown(false);
            break;

        case SDLK_LEFT:
            actions.moveLeft(false);
            break;

        case SDLK_RIGHT:
            actions.moveRight(false);
            break;
    }
}

void InputSystem::keydown(SDL_Event const &e)
{
    switch (e.key.keysym.sym)
    {
        case SDLK_UP:
            actions.moveUp(true);
            break;

        case SDLK_DOWN:
            actions.moveDown(true);
            break;

        case SDLK_LEFT:
            actions.moveLeft(true);
            break;

        case SDLK_RIGHT:
            actions.moveRight(true);
            break;
    }
}

void InputSystem::buttonup(SDL_ControllerButtonEvent const &e)
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
            actions.moveUp(false);
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            actions.moveDown(false);
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            actions.moveLeft(false);
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            actions.moveRight(false);
            break;
    }
}

void InputSystem::buttondown(SDL_ControllerButtonEvent const &e)
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
            actions.moveUp(true);
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            actions.moveDown(true);
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            actions.moveLeft(true);
            break;

        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            actions.moveRight(true);
            break;
    }
}