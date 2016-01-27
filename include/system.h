#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "message_bus.h"

class System
{
public:
    System(MessageBus *);
    virtual ~System();

    virtual void handleMessage(Message const &) = 0;
    void sendMessage(const char *, void * = nullptr);

private:
    MessageBus * bus;
};

#endif // _SYSTEM_H_