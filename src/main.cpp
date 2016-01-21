#include <stdio.h>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>

#include <sprite.h>
#include <animated_sprite.h>
#include <square.h>
#include <actions.h>

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 420;

void destroy(SDL_Window * ptr)
{
    if (ptr)
    {
        SDL_DestroyWindow(ptr);
    }
}

void destroy(SDL_Renderer * ptr)
{
    if (ptr)
    {
        SDL_DestroyRenderer(ptr);
    }
}

bool input(SDL_Event * e, Actions * actions)
{
    while (SDL_PollEvent(e) != 0)
    {
        if (e->type == SDL_QUIT)
        {
            return true;
        }
        else if (e->type == SDL_KEYDOWN)
        {
            actions->keydown(e);
        }
        else if (e->type == SDL_KEYUP)
        {
            actions->keyup(e);
        }
    }
    return false;
}

void update(Actions const &actions, Square * display_object)
{
    if (actions.enabled(ACTION_UP))
    {
        display_object->y(display_object->y() - 1, SCREEN_HEIGHT);
    }

    if (actions.enabled(ACTION_DOWN))
    {
        display_object->y(display_object->y() + 1, SCREEN_HEIGHT - display_object->length());
    }

    if (actions.enabled(ACTION_LEFT))
    {
        display_object->x(display_object->x() - 1, SCREEN_WIDTH);
    }

    if (actions.enabled(ACTION_RIGHT))
    {
        display_object->x(display_object->x() + 1, SCREEN_WIDTH - display_object->length());
    }
}

int main(int argc, char * args[])
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | IMG_INIT_PNG) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear texture filtering not enabled!");
    }

    //Create window
    auto window = SDL_CreateWindow("fps : n/a", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create renderer for window
        auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Load media
            Sprite carpet;
            carpet.load("carpet.normal.mobile.png", renderer);

            Sprite frame;
            frame.load("frame.big.mobile.png", renderer);

            AnimatedSprite chips(500);
            chips.load("3dchip.png", renderer);

            Square square(64, { 0xFF, 0x00, 0x00, 0xFF });
            Actions actions;

            bool quit = false;
            SDL_Event e;

            unsigned long frame_time = 0;
            unsigned long second_time = SDL_GetTicks();
            unsigned long render_time = 0;
            unsigned long update_time = 0;

            int fps_counter = 0;
            int update_counter = 0;
            int dt = 0;

            chips.clip(45, 45, false);
            // chips.center(SCREEN_WIDTH, SCREEN_HEIGHT);
            square.center(SCREEN_WIDTH, SCREEN_HEIGHT);

            while (!quit)
            {
                frame_time = SDL_GetTicks();

                //Handle events on queue
                quit = input(&e, &actions);

                //Update models logic (200Hz)
                if ((frame_time - update_time) >= 5)
                {
                    ++update_counter;
                    update_time = frame_time;

                    update(actions, &square);
                }

                //Refresh screen (~60Hz)
                dt = frame_time - render_time;
                if (dt >= 16)
                {
                    ++fps_counter;
                    render_time = frame_time;

                    chips.update(dt);

                    //Clear screen
                    SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xFF);
                    SDL_RenderClear(renderer);

                    //Render texture to screen
                    frame.render(renderer);
                    carpet.render(renderer);
                    chips.render(renderer);

                    square.render(renderer);

                    //Update screen
                    SDL_RenderPresent(renderer);
                }

                if ((frame_time - second_time) >= 1000)
                {
                    second_time = frame_time;

                    std::ostringstream ss;
                    ss << "Hz : " << fps_counter << " - " << update_counter;

                    SDL_SetWindowTitle(window, ss.str().c_str());
                    fps_counter = 0;
                    update_counter = 0;
                }
            }

            destroy(renderer);
        }

        //Destroy window
        destroy(window);
    }

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}