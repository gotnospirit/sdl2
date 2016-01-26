#include <iostream>
#include <sstream>
#include <cstring>

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
}

bool RenderSystem::initialize()
{
    int flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags))
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    if (!window)
    {
        //Create window
        window = SDL_CreateWindow("Hz : n/a", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    }

    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!renderer)
    {
        //Create renderer for window
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!ttf)
    {
        ttf = new Font();
    }

    if (!ttf->load("Montserrat-Regular.ttf", 16))
    {
        std::cerr << "Cannot load font!" << std::endl;
        return false;
    }
    return true;
}

RenderSystem::~RenderSystem()
{
    for (auto &object : objects)
    {
        delete object;
    }

    delete ttf;

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

void RenderSystem::handleMessage(const char * msg, size_t msglen)
{
    if (0 == strncmp(msg, "CREATE ", 7))
    {
        if (0 == strcmp(msg + 7, "TABLE"))
        {
            auto frame = new Sprite();
            frame->load("frame.big.mobile.png", renderer);
            objects.push_back(frame);

            auto carpet = new Sprite();
            carpet->load("carpet.normal.mobile.png", renderer);
            objects.push_back(carpet);
        }
        else if (0 == strcmp(msg + 7, "CHIPS"))
        {
            auto chips = new Spritesheet(500);
            chips->load("3dchip.png", renderer);
            chips->clip(0, 0, 45, 45);
            chips->orientation(false);
            chips->center(SCREEN_WIDTH, SCREEN_HEIGHT);
            objects.push_back(chips);

            target = chips;
        }
        else if (0 == strcmp(msg + 7, "SQUARE"))
        {
            auto square = new Square(64);
            square->setColor(0xFF, 0x00, 0x00);
            square->clip(0, 0, square->getWidth(), square->getHeight() - 10);
            square->center(SCREEN_WIDTH, SCREEN_HEIGHT);
            objects.push_back(square);
        }
        else if (0 == strcmp(msg + 7, "GUY"))
        {
            auto guy = new Sprite();
            guy->load("foo.png", renderer, { 0, 0xFF, 0xFF });
            guy->clip(0, 0, guy->getWidth(), 100);
            guy->setColor(0x00, 0x00, 0xff);
            guy->setY(SCREEN_HEIGHT - guy->getHeight());
            objects.push_back(guy);
        }
        else if (0 == strncmp(msg + 7, "TEXT ", 5) && msglen > 12)
        {
            auto myText = new Sprite();
            myText->setTexture(ttf->render(msg + 12, 0, 0, 0, renderer, true));
            objects.push_back(myText);

            // auto dim = ttf->measure(msg + 5);
            // std::cout << "Measure '" << (msg + 5) << "': " << dim.w << "x" << dim.h << std::endl;
        }
    }
    else if (0 == strncmp(msg, "COUNTER ", 8))
    {
        if (0 == strcmp(msg + 8, "UPDATE"))
        {
            ++update_counter;
        }
    }
    else if (0 == strncmp(msg, "ACTION MOVE ", 12))
    {
        if (target)
        {
            if (0 == strncmp(msg + 12, "UP", 2))
            {
                target->setY(clamp(target->getY() - 1, 0, SCREEN_HEIGHT));
            }
            else if (0 == strncmp(msg + 12, "DOWN", 4))
            {
                target->setY(clamp(target->getY() + 1, 0, SCREEN_HEIGHT - target->getHeight()));
            }
            else if (0 == strncmp(msg + 12, "LEFT", 4))
            {
                target->setX(clamp(target->getX() - 1, 0, SCREEN_WIDTH));
            }
            else if (0 == strncmp(msg + 12, "RIGHT", 5))
            {
                target->setX(clamp(target->getX() + 1, 0, SCREEN_WIDTH - target->getWidth()));
            }
        }
    }
    else if (0 == strncmp(msg, "TICK ", 5) && msglen > 5)
    {
        unsigned long frame_time = atoi(msg + 5);

        if ((frame_time - second_time) >= 1000)
        {
            second_time = frame_time;

            std::ostringstream ss;
            ss << "Hz : " << fps_counter << " - " << update_counter;

            SDL_SetWindowTitle(window, ss.str().c_str());
            fps_counter = 0;
            update_counter = 0;
        }

        //Refresh screen (~60Hz)
        auto dt = frame_time - render_time;
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