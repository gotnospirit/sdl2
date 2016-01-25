#ifndef _ACTIONS_H_
#define _ACTIONS_H_

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

    void moveUp(bool);
    void moveDown(bool);
    void moveLeft(bool);
    void moveRight(bool);

    bool enabled(int) const;

private:
    bool data[ACTION_COUNT];
};

#endif // _ACTIONS_H_