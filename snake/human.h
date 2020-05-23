#pragma once
#include <stdio.h>
#include "game.h"
#include "control.h"

class Human: public Control
{
public:
    Human(Snake* s);
    ~Human();
    bool onkey(char key);
};
