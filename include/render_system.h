#ifndef _RENDER_SYSTEM_H_
#define _RENDER_SYSTEM_H_

#include <cstdlib>
#include <vector>

#include <SDL.h>

#include "system.h"
#include "message_bus.h"
#include "font.h"
#include "display_object.h"

class RenderSystem :
    public System
{
public:
    RenderSystem(MessageBus *);
    ~RenderSystem();

    bool initialize();

    void handleMessage(const char *, size_t);

private:
    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;
    Font * ttf = nullptr;

    SDL_Color bgcolor;

    std::vector<DisplayObject *> objects;
    DisplayObject * target = nullptr;

    int fps_counter = 0;
    int update_counter = 0;

    unsigned long render_time = 0;
    unsigned long second_time = 0;
};

#endif // _RENDER_SYSTEM_H_