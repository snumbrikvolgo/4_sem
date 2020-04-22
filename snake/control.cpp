#include "control.h"
#include "game.h"
Control::Control(Snake * s)
{
    snake = s;
    snake -> brand = 0;
}

Control::~Control()
{
}
