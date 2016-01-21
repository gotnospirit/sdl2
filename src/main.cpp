#include <stdio.h>
#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 420;

enum ACTION {
    ACTION_UP,
    ACTION_DOWN,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_COUNT
};

std::string getFilepath(const char * filename)
{
    std::ostringstream ss;
    ss << SDL_GetBasePath() << filename;
    return ss.str();
}

int clamp(int value, int min, int max)
{
    if (value > max)
    {
        return max;
    }
    else if (value < min)
    {
        return min;
    }
    return value;
}

SDL_Texture * loadTexture(std::string const &filepath, SDL_Renderer * renderer)
{
    //The final texture
    SDL_Texture * newTexture = nullptr;

    //Load image at specified path
    printf("Loading texture '%s'\n", filepath.c_str());

    SDL_Surface * loadedSurface = IMG_Load(filepath.c_str());
    if (!loadedSurface)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filepath.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!newTexture)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool render(SDL_Texture * source, SDL_Renderer * renderer, bool stretch)
{
    if (source)
    {
        if (stretch)
        {
            return 0 == SDL_RenderCopy(renderer, source, NULL, NULL);
        }

        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = SCREEN_WIDTH;
        rect.h = SCREEN_HEIGHT;

        SDL_QueryTexture(source, NULL, NULL, &rect.w, &rect.h);

        return 0 == SDL_RenderCopy(renderer, source, NULL, &rect);
    }
    return false;
}

void drawShape(SDL_Rect const &rect, SDL_Color const &color, SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

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

void destroy(SDL_Texture * ptr)
{
    if (ptr)
    {
        SDL_DestroyTexture(ptr);
    }
}

bool input(SDL_Event * e, bool * actions)
{
    while (SDL_PollEvent(e) != 0)
    {
        if (e->type == SDL_QUIT)
        {
            return true;
        }
        else if (e->type == SDL_KEYDOWN)
        {
            switch (e->key.keysym.sym)
            {
                case SDLK_UP:
                    actions[ACTION_UP] = true;
                    break;

                case SDLK_DOWN:
                    actions[ACTION_DOWN] = true;
                    break;

                case SDLK_LEFT:
                    actions[ACTION_LEFT] = true;
                    break;

                case SDLK_RIGHT:
                    actions[ACTION_RIGHT] = true;
                    break;
            }
        }
        else if (e->type == SDL_KEYUP)
        {
            switch (e->key.keysym.sym)
            {
                case SDLK_UP:
                    actions[ACTION_UP] = false;
                    break;

                case SDLK_DOWN:
                    actions[ACTION_DOWN] = false;
                    break;

                case SDLK_LEFT:
                    actions[ACTION_LEFT] = false;
                    break;

                case SDLK_RIGHT:
                    actions[ACTION_RIGHT] = false;
                    break;
            }
        }
    }
    return false;
}

void update(bool * actions, SDL_Rect * state, int square_width)
{
    if (actions[ACTION_UP])
    {
        state->y = clamp(state->y - 1, 0, SCREEN_HEIGHT);
    }

    if (actions[ACTION_DOWN])
    {
        state->y = clamp(state->y + 1, 0, SCREEN_HEIGHT - square_width);
    }

    if (actions[ACTION_LEFT])
    {
        state->x = clamp(state->x - 1, 0, SCREEN_WIDTH);
    }

    if (actions[ACTION_RIGHT])
    {
        state->x = clamp(state->x + 1, 0, SCREEN_WIDTH - square_width);
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
            auto carpet = loadTexture(getFilepath("carpet.normal.mobile.png"), renderer);
            auto frame = loadTexture(getFilepath("frame.big.mobile.png"), renderer);

            bool quit = false;
            SDL_Event e;
            int side = 64;
            SDL_Rect rect { (SCREEN_WIDTH - side) / 2, (SCREEN_HEIGHT - side) / 2, side, side };

            unsigned long frame_time = 0;
            unsigned long second_time = SDL_GetTicks();
            unsigned long render_time = 0;
            unsigned long update_time = 0;

            int fps_counter = 0;
            int update_counter = 0;

            bool actions[ACTION_COUNT];
            actions[ACTION_UP] = false;
            actions[ACTION_DOWN] = false;
            actions[ACTION_LEFT] = false;
            actions[ACTION_RIGHT] = false;

            while (!quit)
            {
                frame_time = SDL_GetTicks();

                //Handle events on queue
                quit = input(&e, actions);

                //Update models logic (200Hz)
                if ((frame_time - update_time) >= 5)
                {
                    ++update_counter;
                    update_time = frame_time;

                    update(actions, &rect, side);
                }

                //Refresh screen (~60Hz)
                if ((frame_time - render_time) >= 16)
                {
                    ++fps_counter;
                    render_time = frame_time;

                    //Clear screen
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(renderer);

                    //Render texture to screen
                    render(frame, renderer, false);
                    render(carpet, renderer, false);

                    drawShape(
                        rect,
                        { 0xFF, 0x00, 0x00, 0xFF },
                        renderer
                    );

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

            //Deallocate textures
            destroy(carpet);
            destroy(frame);

            destroy(renderer);
        }

        //Destroy window
        destroy(window);
    }

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}