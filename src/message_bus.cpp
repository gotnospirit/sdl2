#include "message_bus.h"
#include "system.h"

Message::Message(const char * type, void * data) :
    type(type),
    data(data)
{
}

void MessageBus::attach(System * o)
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

void MessageBus::detach(System * o)
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

void MessageBus::dispatch(const char * type, void * data) const
{
    Message msg(type, data);

    for (auto system : systems)
    {
        system->handleMessage(msg);
    }
}