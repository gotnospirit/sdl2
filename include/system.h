#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "message_bus.h"

class System
{
public:
    System(MessageBus *);
    virtual ~System();

    virtual void handleMessage(const char *, size_t) = 0;
    void sendMessage(const char *);

private:
    MessageBus * mbus;
};

#endif // _SYSTEM_H_