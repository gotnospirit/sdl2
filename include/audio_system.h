#ifndef _AUDIO_SYSTEM_H_
#define _AUDIO_SYSTEM_H_

#include <SDL_mixer.h>

#include "system.h"
#include "message_bus.h"

class AudioSystem :
    public System
{
public:
    AudioSystem(MessageBus *);
    ~AudioSystem();

    void handleMessage(Message const &);

private:
    Mix_Music * bgmusic = nullptr;
};

#endif // _AUDIO_SYSTEM_H_