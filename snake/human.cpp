#pragma once
#include "human.h"
#include "ui.h"
#include <stdio.h>


Human::Human(Snake* s): Control(s)
{
    s -> brand = 3;
    Ui* v = Ui::get();
    v->set_on_key(this);
}


Human::~Human()
{
}


bool Human::onkey(char key)
{
    switch (key) {
        case 'a':
            if(snake->dir == LEFT)  break;
            snake->set_direction(LEFT);
            break;

        case 'd':
            if(snake->dir == RIGHT)  break;
            snake->set_direction(RIGHT);
            break;

        case 'w':
            if(snake->dir == UP)  break;
            snake->set_direction(UP);
            break;

        case 's':
            if(snake->dir == DOWN)  break;
            snake->set_direction(DOWN);
            break;

        default:
            break;
    }
}
