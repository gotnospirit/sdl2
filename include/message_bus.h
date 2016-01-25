#ifndef _MESSAGE_BUS_H_
#define _MESSAGE_BUS_H_

#include <vector>

class System;

class MessageBus
{
public:
    void add(System *);
    void remove(System *);

    void dispatch(const char *) const;

private:
    std::vector<System *> systems;
};

#endif // _MESSAGE_BUS_H_