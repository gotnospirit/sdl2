#include <stdio.h>
#include <iostream>

#include <SDL.h>

#include "message_bus.h"
#include "input_system.h"
#include "render_system.h"

int main(int argc, char * args[])
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    {
        MessageBus bus;

        InputSystem input(&bus);
        RenderSystem render(&bus);

        bus.dispatch("CREATE TABLE");
        bus.dispatch("CREATE SQUARE");
        bus.dispatch("CREATE GUY");
        bus.dispatch("CREATE CHIPS");
        bus.dispatch("CREATE TEXT", (void *)"Hello James");

        while (input.poll())
        {
            bus.dispatch("TICK", (void *)(uintptr_t)SDL_GetTicks());
        }
    }

	SDL_Quit();

	return 0;
}