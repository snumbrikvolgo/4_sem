#pragma once
#include <stdio.h>

class Key
{
public:
    virtual bool onkey(char key) = 0;
};
