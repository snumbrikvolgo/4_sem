#pragma once
#include <stdio.h>
#include "game.h"
#include "control.h"
#include "key.h"


class Human : public Control, public Key
{
public:
    Human(Snake* s);
    ~Human();
    bool onkey(char key);
};
