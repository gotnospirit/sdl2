#include <iostream>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "render_system.h"
#include "utils.h"

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 420;

RenderSystem::RenderSystem(MessageBus * bus) :
    System(bus),
    chips(500),
    square(64),
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

    //Create window
    window = SDL_CreateWindow("Hz : n/a", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        //Create renderer for window
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            ttf = new Font();

            if (!ttf->load("Montserrat-Regular.ttf", 16))
            {
                std::cerr << "Cannot load font!" << std::endl;
                return false;
            }
        }
    }
    return true;
}

RenderSystem::~RenderSystem()
{
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
    if (0 == strcmp(msg, "SHOW_TABLE"))
    {
        carpet.load("carpet.normal.mobile.png", renderer);
        frame.load("frame.big.mobile.png", renderer);
    }
    else if (0 == strcmp(msg, "SHOW_CHIPS"))
    {
        chips.load("3dchip.png", renderer);
        chips.clip(0, 0, 45, 45);
        chips.orientation(false);
        chips.center(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else if (0 == strcmp(msg, "SHOW_SQUARE"))
    {
        square.setColor(0xFF, 0x00, 0x00);
        square.clip(0, 0, square.getWidth(), square.getHeight() - 10);
        square.center(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else if (0 == strcmp(msg, "SHOW_GUY"))
    {
        guy.load("foo.png", renderer, { 0, 0xFF, 0xFF });
        guy.clip(0, 0, guy.getWidth(), 100);
        guy.setColor(0x00, 0x00, 0xff);
        guy.setY(SCREEN_HEIGHT - guy.getHeight());
    }
    else if (0 == strcmp(msg, "UPDATE"))
    {
        ++update_counter;
    }
    else if (0 == strncmp(msg, "MOVE ", 5))
    {
        if (0 == strncmp(msg + 5, "UP", 2))
        {
            chips.setY(clamp(chips.getY() - 1, 0, SCREEN_HEIGHT));
        }
        else if (0 == strncmp(msg + 5, "DOWN", 4))
        {
            chips.setY(clamp(chips.getY() + 1, 0, SCREEN_HEIGHT - chips.getHeight()));
        }
        else if (0 == strncmp(msg + 5, "LEFT", 4))
        {
            chips.setX(clamp(chips.getX() - 1, 0, SCREEN_WIDTH));
        }
        else if (0 == strncmp(msg + 5, "RIGHT", 5))
        {
            chips.setX(clamp(chips.getX() + 1, 0, SCREEN_WIDTH - chips.getWidth()));
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

            chips.update(dt);

            //Clear screen
            SDL_SetRenderDrawColor(renderer, bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a);
            SDL_RenderClear(renderer);

            //Render texture to screen
            frame.render(renderer);
            carpet.render(renderer);
            guy.render(renderer);

            square.render(renderer);
            chips.render(renderer);
            myText.render(renderer);

            //Update screen
            SDL_RenderPresent(renderer);
        }
    }
    else if (0 == strncmp(msg, "TEXT ", 5) && msglen > 5)
    {
        myText.setTexture(ttf->render(msg + 5, 0, 0, 0, renderer, true));

        // auto dim = ttf->measure(msg + 5);
        // std::cout << "Measure '" << (msg + 5) << "': " << dim.w << "x" << dim.h << std::endl;
    }
}