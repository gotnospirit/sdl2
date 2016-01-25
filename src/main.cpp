#include <stdio.h>
#include <sstream>
#include <iostream>

#include <SDL.h>

#include "message_bus.h"
#include "input_system.h"
#include "render_system.h"

int main(int argc, char * args[])
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    {
        MessageBus bus;

        InputSystem input(&bus);
        RenderSystem render(&bus);

        render.initialize();

        bus.add(&input);
        bus.add(&render);

        bus.dispatch("SHOW_TABLE");
        bus.dispatch("SHOW_CHIPS");
        bus.dispatch("SHOW_SQUARE");
        bus.dispatch("SHOW_GUY");
        bus.dispatch("TEXT Hello James");

        while (input.poll())
        {
            std::ostringstream ss;
            ss << "TICK " << SDL_GetTicks();

            bus.dispatch(ss.str().c_str());
        }
    }

	SDL_Quit();

	return 0;
}