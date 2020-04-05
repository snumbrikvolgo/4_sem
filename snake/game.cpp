#include "ui.h"
#include "game.h"
#include <iostream>

#define RAABBIT_TIME 4
#define SNAKE_TIME 400000000

Game * Game::inst;

Game * Game::get()
{
    if(inst != nullptr)    return Game::inst;
    Game::inst = new Game;
    return Game::inst;
}

Game::Game()
{
    Ui* v = Ui::get();
    struct timespec t;



}

void Game::add(Snake& s)
{
    snakes.push_back(s);
}

Coord Game::GetFreeCoord()
{
    Coord c;

    while(1)
    {
        c.first = rand() % Ui::get()->winx();
        c.second = rand() % Ui::get()->winy();

        if(c.first == 0 || c.first == 1)    c.first += 5;// worktime.tv_nsec % rand() % View::get()->x;
        if(c.second == 0 || c.second == 1)   c.second += 5;// worktime.tv_nsec % View::get()->y;

        if(c.first == Ui::get()->winx()- 1)     c.first -= 5;
        if(c.second == Ui::get()->winy() - 1)     c.second -= 5;

    }
    return c;
}


Snake::Snake()
{
    alive = true;
    dir = UP;

    Coord c = Game::get()->GetFreeCoord();
    body.push_back(Coord(++c.first, c.second));
    body.push_back(Coord(++c.first, c.second));
    body.push_back(Coord(++c.first, c.second));

}

void Snake::set_direction(Dir d)
{
    if((d == LEFT || d == RIGHT) && (dir == LEFT || dir == RIGHT))  return;
    if((d == UP || d == DOWN) && (dir == UP || dir == DOWN))  return;
    dir = d;
}
