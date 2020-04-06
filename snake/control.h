#pragma once
#include <stdio.h>

class Snake;

class Control
{
public:
    Control(Snake* s);
    ~Control();

    Snake* snake;
};
