#include "game.h"
#include "ui.h"
#include "AI.h"
#include <iostream>

#define RABIT_TIME 5
#define SNAKE_TIME 300000000

Game* Game::inst;
int Game::snake_number;

Game * Game::get()
{
    if(inst != nullptr)
        return Game::inst;
    Game::inst = new Game();
    return Game::inst;
}

void Game::paint(SnakePainter ps, RabbitPainter pr, ScorePainter psc)
{
    for(const auto s : snakes) {
        //std::cerr << s -> brand  << " snwk brand"<< std::endl;
        bool head = false;

        for(const auto & c : s -> body) {
            ps(c, head ? BODY : s -> dir, s->brand);
            head = true;
        }
        psc(s -> snake_score, s -> brand);
    }

    for(const auto & r : rabbits) {
        pr(r);
    }
}

Game::Game()
{
    Ui* v = Ui::get();
    struct timespec t;

    for(int i = 0; i < MAX_RABBITS; i ++) {
        rabbit_generate();
        Ui::get()->ontime_delegater.pop_back();
    }

    t = {0, SNAKE_TIME};
    v->set_on_timer(t, std::bind(&Game::move, this));

    t = {RABIT_TIME, 0};
    v->set_on_timer(t, std::bind(&Game::rabbit_generate, this));

    snake_number = 0;

}

void Game::add(Snake* s)
{
    //std::cerr<< s->brand << " snake color in add" << std::endl;
    s -> brand = snake_number;
    snakes.push_back(s);
    snake_number++;
}

Coord Game::get_free_coord()
{
    Coord c;
    while(1)
    {
        c.first  = rand() % Ui::get()->winx();
        c.second = rand() % Ui::get()->winy();

        if(c.first  == 0 || c.first  == 1)    c.first  += 5;
        if(c.second == 0 || c.second == 1)    c.second += 5;

        if(c.first  == Ui::get()->winx() - 1)     c.first  -= 5;
        if(c.second == Ui::get()->winy() - 1)     c.second -= 5;

        if(check_place(c)) {
            return c;
            }
    }
}

void Game::rabbit_generate()
{
    Coord c;
    srand(time(NULL));

    struct timespec t;
    t = {RABIT_TIME, 0};
    Ui::get()->set_on_timer(t, std::bind(&Game::rabbit_generate, this));

    while(1) {
        c.first  = rand() % Ui::get()->winx();
        c.second = rand() % Ui::get()->winy();

        if(c.first  == 0)     c.first ++;
        if(c.second == 0)    c.second ++;

        if(c.first  == Ui::get()->winx() - 1)     c.first  --;
        if(c.second == Ui::get()->winy() - 1)     c.second --;

        if(check_place(c)) {
            rabbits.push_back(c);
            return;
        }
    }
}

Snake::Snake()
{
    alive = true;
    dir = DOWN;
    //brand = 10;

    Coord c = Game::get() -> get_free_coord();

     body.push_back(Coord(++c.first, c.second));
     body.push_back(Coord(++c.first, c.second));
     body.push_back(Coord(++c.first, c.second));

     std::freopen( "error.txt", "wr", stderr );
     std::cerr << brand  << " kek"<< std::endl;

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

    Ui::get()->AI_delegater->on_move();

    for(auto s: snakes)
        if(s->alive)
            s->move();

    Ui::get()->draw();

    struct timespec t;
    t = {0, SNAKE_TIME};
    Ui::get()->set_on_timer(t, std::bind(&Game::move, this));
}

void Snake::set_direction(Dir d)
{
    if((d == LEFT || d == RIGHT) && (dir == LEFT || dir == RIGHT))  return;
    if((d == UP || d == DOWN) && (dir == UP || dir == DOWN))  return;
    dir = d;
}

Coord Snake::next_position(Dir d, Coord a)
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

Coord Game::nearest_rabbit(Coord c)
{
    if(rabbits.size() == 0) return Coord(0, 0);

    Coord rab(0, 0);
    int min = rabbits.front().distance(c);
    rab = rabbits.front();

    for(auto p : rabbits)
    {
        if(min > p.distance(c)) {
            min = p.distance(c);
            rab = p;
        }
    }
    return rab;
}

char Game::check_place_snake(Coord c)
{
    for(const auto s : snakes)
        for(const auto & sb : s->body)
            if(c == sb)  return 's';

    for(const auto & r : rabbits)
        if(c == r)
        {
            return 'r';
        }

    if(c.first == 1 || c.second == 1 || c.second == Ui::get()->winx() || c.second == Ui::get()->winy()) return 'b';

    return ' ';
}

void Snake::move()
{
    Coord a = body.front();
    a = next_position(dir, a);

    switch (Game::get()->check_place_snake(a)) {
        case ' ':
            body.push_front(a);
            body.pop_back();
            break;

        case 's':
            alive = false;
            break;

        case 'b':
            alive = false;
            break;

        case 'r':
        {
            Game::get()->kill_rabbit(a);
            //snake_score++;
            body.push_front(a);
            break;
        }

        default:
            break;
    }
}

void Game::kill_rabbit(Coord c)
{
    for(const auto & r : rabbits)
        if(c == r)
        {
            rabbits.remove(r);
            return;
        }
}

bool Game::check_place(Coord c)
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
