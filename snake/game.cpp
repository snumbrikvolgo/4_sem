#include "game.h"
#include "ui.h"

#include "AI.h"
#include <iostream>

#define RAABBIT_TIME 4
#define SNAKE_TIME 400000000

Game * Game::inst;

Game * Game::get()
{
    if(inst != nullptr)    {return Game::inst;}
    Game::inst = new Game();
    return Game::inst;
}
void Game::paint(SnakePainter ps, RabbitPainter pr)
{
    for(const auto s : snakes) {

        bool head = false;

        for(const auto & c : s->body) {
            ps(c, head ? BODY : s->dir);
            head = true;
        }
    }

    for(const auto & r : rabbits) {
        pr(r);
    }
}

Game::Game()
{
    Ui* v = Ui::get();
    struct timespec t;

    for(int i = 0; i < 15; i ++) {
    rabbitgenerate();
    Ui::get()->ontime_deligater.pop_back();
    }

    t = {0, SNAKE_TIME};
    v->setontimer(t, std::bind(&Game::move, this));

    t = {RAABBIT_TIME, 0};
    v->setontimer(t, std::bind(&Game::rabbitgenerate, this));

}

void Game::add(Snake* s)
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

        if(c.first == 0 || c.first == 1)    c.first += 5;// worktime.tv_nsec % rand() % Ui::get()->x;
        if(c.second == 0 || c.second == 1)   c.second += 5;// worktime.tv_nsec % Ui::get()->y;

        if(c.first == Ui::get()->winx()- 1)     c.first -= 5;
        if(c.second == Ui::get()->winy() - 1)     c.second -= 5;

        if(checkplace(c)) {
            return c;
        }
    }
}

void Game::rabbitgenerate()
{
    Coord c;
    srand(5);

    struct timespec t;
    t = {RAABBIT_TIME, 0};
    Ui::get()->setontimer(t, std::bind(&Game::rabbitgenerate, this));

    while(1) {
        //printf("hui\n" );
        c.first = rand() % Ui::get()->winx();
        c.second = rand() % Ui::get()->winy();

        if(c.first == 0)     c.first ++;
        if(c.second == 0)    c.second ++;

        if(c.first == Ui::get()->winx() - 1)     c.first --;
        if(c.second == Ui::get()->winy() - 1)     c.second --;

        if(checkplace(c)) {
            rabbits.push_back(c);
            return;
        }
    }
}

Snake::Snake()
{
    alive = true;
    dir = DOWN;

    Coord c = Game::get()->GetFreeCoord();
    // Coord c;
    // c.first = 5;
    // c.second  = 6;

    //std::cout<< Game::get() << std::endl;
     body.push_back(Coord(++c.first, c.second));
     body.push_back(Coord(++c.first, c.second));
     body.push_back(Coord(++c.first, c.second));

}

void Game::move()
{
    bool all_die = true;

    for(auto s: snakes)
        if(s->alive)
        {
            all_die = false;
            break;
        }

    if(all_die)
    {
        Ui::get()->~Ui();
    }

    Ui::get()->AI_deligater->OnMove();

    for(auto s: snakes)
        if(s->alive)
            s->move();

    Ui::get()->draw();

    struct timespec t;
    t = {0, SNAKE_TIME};
    Ui::get()->setontimer(t, std::bind(&Game::move, this));
}

void Snake::set_direction(Dir d)
{
    if((d == LEFT || d == RIGHT) && (dir == LEFT || dir == RIGHT))  return;
    if((d == UP || d == DOWN) && (dir == UP || dir == DOWN))  return;
    dir = d;
}

Coord Snake::NextPosition(Dir d, Coord a)
{
    switch (d) {
        case UP:
            a.second ++;
            break;

        case DOWN:
            a.second --;
            break;

        case LEFT:
            a.first --;
            break;

        case RIGHT:
            a.first ++;
            break;

        default:
            break;


    }
    return a;
}


Coord Game::near(Coord c)
{

    if(rabbits.size() == 0) return Coord(0, 0);

    Coord r(0, 0);
    int min = rabbits.front().distance(c);
    r = rabbits.front();

    for(auto p : rabbits)
    {
        if(min > p.distance(c)) {
            min = p.distance(c);
            r = p;
        }
    }
    return r;
}

char Game::checkplacesnake(Coord c)
{
    for(const auto s : snakes)
        for(const auto & sb : s->body)
            if(c == sb)  return 's';

    for(const auto & r : rabbits)
        if(c == r)
        {
            //rabbits.remove(r);
            return 'r';
        }

    if(c.first == 1 || c.second == 1 || c.second == Ui::get()->winx() || c.second == Ui::get()->winy()) return 'b';

    return ' ';
}

void Snake::move()
{
    Coord a = body.front();

    a = NextPosition(dir, a);

    //body.push_front(a);
    switch (Game::get()->checkplacesnake(a)) {
        case ' ':
            body.push_front(a);
            body.pop_back();
            break;

        case 's':
            alive = false;
            //Ui::get()->~Ui();
            break;

        case 'b':
            alive = false;
            //Ui::get()->~Ui();
            break;

        case 'r':
        {
            Game::get()->KillRabbit(a);
            body.push_front(a);
            break;
        }

        default:
            break;
    }
}

void Game::KillRabbit(Coord c)
{
    for(const auto & r : rabbits)
        if(c == r)
        {
            rabbits.remove(r);
            return;
        }
}
bool Game::checkplace(Coord c)
{
    for(const auto s : snakes)
        for(const auto & sb : s->body)
            if(c == sb) return false;

    for(const auto & r : rabbits)
        if(c == r) return false;

    if(c.first >= 0 && c.first <= 1)    return false;
    if(c.second >= 0 && c.second <= 1)   return false;

    if(c.first >= Ui::get()->winx() - 1)     return false;
    if(c.second >= Ui::get()->winy() - 1)     return false;

    return true;
}
