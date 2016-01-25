#include "system.h"

System::System(MessageBus * bus) :
    mbus(bus)
{
}

System::~System()
{
    mbus->remove(this);
}

void System::sendMessage(const char * msg)
{
    mbus->dispatch(msg);
}