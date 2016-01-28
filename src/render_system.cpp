#include <iostream>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "render_system.h"
#include "sprite.h"
#include "spritesheet.h"
#include "square.h"
#include "utils.h"

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 420;

RenderSystem::RenderSystem(MessageBus * bus) :
    System(bus),
    bgcolor({ 0xcc, 0xcc, 0xcc, 0xFF })
{
    int flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags))
    {
        throw IMG_GetError();
    }

    if (TTF_Init() == -1)
    {
        throw TTF_GetError();
    }

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    //Create window
    window = SDL_CreateWindow("Hz : n/a", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        throw SDL_GetError();
    }

    //Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        throw SDL_GetError();
    }

    ttf = new Font();
}

RenderSystem::~RenderSystem()
{
    for (auto &object : objects)
    {
        delete object;
    }

    if (ttf)
    {
        delete ttf;
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }

    if (window)
    {
        SDL_DestroyWindow(window);
    }

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
}

void RenderSystem::handleMessage(Message const &msg)
{
    if (0 == strncmp(msg.type, "CREATE ", 7))
    {
        if (0 == strcmp(msg.type + 7, "TABLE"))
        {
            auto frame = new Sprite();
            if (frame->load("frame.big.mobile.png", renderer))
            {
                objects.push_back(frame);
            }
            else
            {
                delete frame;
            }

            auto carpet = new Sprite();
            if (carpet->load("carpet.normal.mobile.png", renderer))
            {
                objects.push_back(carpet);
            }
            else
            {
                delete carpet;
            }
        }
        else if (0 == strcmp(msg.type + 7, "CHIPS"))
        {
            auto chips = new Spritesheet();
            if (chips->load("3dchip.png", renderer))
            {
                chips->duration(500);
                chips->clip(0, 0, 45, 45);
                chips->orientation(false);
                chips->center(SCREEN_WIDTH, SCREEN_HEIGHT);
                objects.push_back(chips);
                target = chips;
            }
            else
            {
                delete chips;
            }
        }
        else if (0 == strcmp(msg.type + 7, "SQUARE"))
        {
            auto square = new Square();
            square->size(64);
            square->color(0xFF, 0x00, 0x00);
            square->clip(0, 0, square->width(), square->height() - 10);
            square->center(SCREEN_WIDTH, SCREEN_HEIGHT);
            objects.push_back(square);
        }
        else if (0 == strcmp(msg.type + 7, "GUY"))
        {
            auto guy = new Sprite();
            if (guy->load("foo.png", renderer, { 0, 0xFF, 0xFF }))
            {
                guy->clip(0, 0, guy->width(), 100);
                guy->color(0x00, 0x00, 0xff);
                guy->y(SCREEN_HEIGHT - guy->height());
                objects.push_back(guy);
            }
            else
            {
                delete guy;
            }
        }
        else if (0 == strncmp(msg.type + 7, "TEXT", 4) && msg.data)
        {
            auto text = ttf->render(static_cast<const char *>(msg.data), 0, 0, 0, "Montserrat-Regular.ttf", 16, renderer, true);
            if (text)
            {
                auto myText = new Sprite();
                myText->setTexture(text);
                objects.push_back(myText);
            }
            // auto dim = ttf->measure(static_cast<const char *>(msg.data), "Montserrat-Regular.ttf", 16);
            // std::cout << "Measure '" << static_cast<const char *>(msg.data) << "': " << dim.w << "x" << dim.h << std::endl;
        }
    }
    else if (0 == strncmp(msg.type, "COUNTER ", 8))
    {
        if (0 == strcmp(msg.type + 8, "UPDATE"))
        {
            ++update_counter;
        }
    }
    else if (0 == strncmp(msg.type, "CURSOR", 6))
    {
        auto const &point = static_cast<const SDL_Point *>(msg.data);

        if (point)
        {
            std::cout << "{ x: " << point->x << ", y: " << point->y << " }" << std::endl;
        }
    }
    else if (0 == strncmp(msg.type, "ACTION", 6) && msg.data)
    {
        if (target)
        {
            auto const action = static_cast<const char *>(msg.data);

            if (0 == strncmp(action, "MOVE UP", 7))
            {
                target->y(clamp(target->y() - 1, 0, SCREEN_HEIGHT));
            }
            else if (0 == strncmp(action, "MOVE DOWN", 9))
            {
                target->y(clamp(target->y() + 1, 0, SCREEN_HEIGHT - target->height()));
            }
            else if (0 == strncmp(action, "MOVE LEFT", 9))
            {
                target->x(clamp(target->x() - 1, 0, SCREEN_WIDTH));
            }
            else if (0 == strncmp(action, "MOVE RIGHT", 10))
            {
                target->x(clamp(target->x() + 1, 0, SCREEN_WIDTH - target->width()));
            }
            else if (0 == strncmp(action, "HOLD ON", 7))
            {
                std::cout << "clicked!" << std::endl;
            }
            else if (0 == strncmp(action, "HOLD OFF", 8))
            {
                std::cout << "unclicked!" << std::endl;
            }
        }
    }
    else if (0 == strncmp(msg.type, "TICK", 4) && msg.data)
    {
        uint32_t frame_time = (uintptr_t)msg.data;
        uint32_t dt = frame_time - second_time;

        if (dt >= 1000)
        {
            second_time = frame_time;

            int nb_seconds = dt / 1000;
            fps_counter /= nb_seconds;
            update_counter /= nb_seconds;

            std::ostringstream ss;
            ss << "Hz : " << fps_counter << " - " << update_counter;

            SDL_SetWindowTitle(window, ss.str().c_str());
            fps_counter = 0;
            update_counter = 0;
        }

        //Refresh screen (max ~60Hz)
        dt = frame_time - render_time;
        if (dt >= 16)
        {
            ++fps_counter;
            render_time = frame_time;

            //Update textures
            for (auto &object : objects)
            {
                object->update(dt);
            }

            //Clear screen
            SDL_SetRenderDrawColor(renderer, bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a);
            SDL_RenderClear(renderer);

            //Render textures to screen
            for (auto &object : objects)
            {
                object->render(renderer);
            }

            //Update screen
            SDL_RenderPresent(renderer);
        }
    }
}