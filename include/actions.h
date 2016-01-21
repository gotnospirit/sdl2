#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include <SDL.h>

enum ACTION {
    ACTION_UP,
    ACTION_DOWN,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_COUNT
};

class Actions
{
public:
    Actions();

    void keyup(SDL_Event const &);
    void keydown(SDL_Event const &);

    bool enabled(int) const;

private:
    bool data[ACTION_COUNT];
};

#endif // _ACTIONS_H_