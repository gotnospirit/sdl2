#include <iostream>

#include <SDL_mixer.h>

#include "audio_system.h"
#include "utils.h"

AudioSystem::AudioSystem(MessageBus * bus) :
    System(bus)
{
    // int flags = MIX_INIT_MP3;
    // if (!(Mix_Init(flags) & flags))
    // {
        // throw Mix_GetError();
    // }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        throw Mix_GetError();
    }
}

AudioSystem::~AudioSystem()
{
    if (bgmusic)
    {
        Mix_FreeMusic(bgmusic);
    }

    Mix_CloseAudio();

    // while (Mix_Init(0))
    // {
        Mix_Quit();
    // }
}

void AudioSystem::handleMessage(Message const &msg)
{
    if (0 == strncmp(msg.type, "START MUSIC", 11))
    {
        if (!bgmusic)
        {
            auto const &filepath = getFilepath("beat.wav");
            std::cout << "Loading '" << filepath << "'" << std::endl;

            bgmusic = Mix_LoadMUS(filepath.c_str());
            if (!bgmusic)
            {
                std::cerr << Mix_GetError() << std::endl;
            }
        }

        if (bgmusic && -1 == Mix_PlayMusic(bgmusic, -1))
        {
            std::cerr << Mix_GetError() << std::endl;
        }
    }
    else if (0 == strncmp(msg.type, "STOP MUSIC", 10) && bgmusic)
    {
        Mix_HaltMusic();
    }
}