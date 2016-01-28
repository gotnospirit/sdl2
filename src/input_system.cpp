#include <iostream>

#include <SDL.h>

#include "input_system.h"

InputSystem::InputSystem(MessageBus * bus) :
    System(bus),
    cursor_moved(false)
{
}

InputSystem::~InputSystem()
{
    if (gamepad)
    {
        SDL_GameControllerClose(gamepad);
    }
}

void InputSystem::handleMessage(Message const &msg)
{
    if (0 == strncmp(msg.type, "TICK", 4) && msg.data)
    {
        uint32_t frame_time = (uintptr_t)msg.data;

        //Update models logic (max 200Hz)
        if ((frame_time - update_time) >= 5)
        {
            update_time = frame_time;

            sendMessage("COUNTER UPDATE");

            if (actions.enabled(ACTION_UP))
            {
                sendMessage("ACTION", (void *)"MOVE UP");
            }

            if (actions.enabled(ACTION_DOWN))
            {
                sendMessage("ACTION", (void *)"MOVE DOWN");
            }

            if (actions.enabled(ACTION_LEFT))
            {
                sendMessage("ACTION", (void *)"MOVE LEFT");
            }

            if (actions.enabled(ACTION_RIGHT))
            {
                sendMessage("ACTION", (void *)"MOVE RIGHT");
            }

            if (cursor_moved)
            {
                cursor_moved = false;

                sendMessage("CURSOR", (void *)&cursor);
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

            case SDL_MOUSEMOTION:
                if (cursor.x != e.motion.x || cursor.y != e.motion.y)
                {
                    cursor.x = e.motion.x;
                    cursor.y = e.motion.y;
                    cursor_moved = true;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    sendMessage("ACTION", (void *)"HOLD ON");
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    sendMessage("ACTION", (void *)"HOLD OFF");
                }
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