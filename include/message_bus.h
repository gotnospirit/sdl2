#ifndef _MESSAGE_BUS_H_
#define _MESSAGE_BUS_H_

#include <vector>

struct Message
{
    Message(const char *, void * = nullptr);

    const char * type;
    void * data;
};

class System;

class MessageBus
{
public:
    void attach(System *);
    void detach(System *);

    void dispatch(const char *, void * = nullptr) const;

private:
    std::vector<System *> systems;
};

#endif // _MESSAGE_BUS_H_