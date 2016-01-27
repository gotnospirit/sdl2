#include "system.h"

System::System(MessageBus * bus) :
    bus(bus)
{
    bus->attach(this);
}

System::~System()
{
    bus->detach(this);
}

void System::sendMessage(const char * type, void * data)
{
    bus->dispatch(type, data);
}