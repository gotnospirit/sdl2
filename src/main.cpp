#include <stdio.h>
#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
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

SDL_Surface * loadSurface(std::string const &filepath, const SDL_PixelFormat * format)
{
    // The final optimized image
    SDL_Surface * optimizedSurface = nullptr;

    // Load image at specified path
    printf("Loading surface '%s'\n", filepath.c_str());

    SDL_Surface * loadedSurface = IMG_Load(filepath.c_str());
    if (!loadedSurface)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filepath.c_str(), IMG_GetError());
    }
    else
    {
        // Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, format, NULL);
        if (!optimizedSurface)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

bool render(SDL_Surface * source, SDL_Surface * destination, bool stretch)
{
    if (source)
    {
        if (stretch)
        {
            SDL_Rect rect { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
            SDL_BlitScaled(source, NULL, destination, &rect);
        }
        else
        {
            SDL_BlitSurface(source, NULL, destination, NULL);
        }
        return true;
    }
    return false;
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

void destroy(SDL_Surface * ptr)
{
    if (ptr)
    {
        SDL_FreeSurface(ptr);
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

bool input(SDL_Event * e, SDL_Rect * state)
{
    //Handle events on queue
    while (SDL_PollEvent(e) != 0)
    {
        //User requests quit
        if (e->type == SDL_QUIT)
        {
            return true;
        }
        //User presses a key
        else if (e->type == SDL_KEYDOWN)
        {
            switch (e->key.keysym.sym)
            {
                case SDLK_UP:
                    state->y = clamp(state->y - 1, 0, SCREEN_HEIGHT);
                    break;

                case SDLK_DOWN:
                    state->y = clamp(state->y + 1, 0, SCREEN_HEIGHT);
                    break;

                case SDLK_LEFT:
                    state->x = clamp(state->x - 1, 0, SCREEN_WIDTH);
                    break;

                case SDLK_RIGHT:
                    state->x = clamp(state->x + 1, 0, SCREEN_WIDTH);
                    break;

                default:
                    break;
            }
        }
    }
    return false;
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
    auto window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // //Get window surface
        // auto screen = SDL_GetWindowSurface(window);

        // //Load media
        // auto carpet = loadSurface(getFilepath("carpet.normal.mobile.png"), screen->format);
        // auto frame = loadSurface(getFilepath("frame.big.mobile.png"), screen->format);

        // if (carpet || frame)
        // {
            // //Apply the image
            // render(frame, screen, false);
            // render(carpet, screen, false);

            // //Update the surface
            // SDL_UpdateWindowSurface(window);
        // }

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

            unsigned long startTime = SDL_GetTicks();
            unsigned long frameTime = 0;

            while (!quit)
            {
                // frameTime = SDL_GetTicks();

                //Handle events on queue
                quit = input(&e, &rect);

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

            //Deallocate textures
            destroy(carpet);
            destroy(frame);

            destroy(renderer);
        }

        // //Deallocate surfaces
        // destroy(carpet);
        // destroy(frame);

        //Destroy window
        destroy(window);
    }

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}