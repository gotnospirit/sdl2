#include <sstream>

#include <SDL.h>

#include "utils.h"

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

float linearEaseIn(int t, float b, float c, int d)
{
    return c * t / d + b;
}