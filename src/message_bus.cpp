#include "message_bus.h"
#include "system.h"

void MessageBus::add(System * o)
{
    bool found = false;
    for (auto system : systems)
    {
        if (system == o)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        systems.push_back(o);
    }
}

void MessageBus::remove(System * o)
{
    for (auto iter = systems.begin(); iter != systems.end();)
    {
        if (*iter == o)
        {
            iter = systems.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void MessageBus::dispatch(const char * msg) const
{
    size_t msglen = strlen(msg);
    for (auto system : systems)
    {
        system->handleMessage(msg, msglen);
    }
}