#include <iostream>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <list>
#include "AI.h"
#include "ui.h"


AI::AI(Snake * s, char manner) : Control(s)
{
    snake = s;
    Ui::get()->set_on_AI(this, manner);
}

AI::~AI(){}

void AI::on_move_dumb()
{
    Dir d[4] = {UP, DOWN, LEFT, RIGHT};

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(d, d + 4, g);
    Coord r = Game::get()->nearest_rabbit(snake->body.front());

    snake->dir = NO;

    bool ok = false;

    Game * game = Game::get();

    if(r != Coord(0, 0)){
        int now = r.distance(snake->body.front());

        for(auto p : d)
        {
            snake->dir = p;
            char next_p = game->check_place_snake(snake->next_position(p, snake->body.front()));
            int next = r.distance(snake->next_position(p, snake->body.front()));
            if(next < now && (next_p == ' ' || next_p == 'r'))
            {
                ok = true;
                break;
            }
        }
    }

    if(!ok)
        for(auto p : d)
        {
            snake->dir = p;
            Coord c = snake->next_position(p, snake->body.front());
            if(game->check_place_snake(c) == ' ')
            {
                //snake->dir = p;
                break;
            }
        }
}

void AI::on_move_clever()
{
    Dir d[4] = {UP, DOWN, LEFT, RIGHT};

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(d, d + 4, g);
    Coord r = Game::get()->nearest_rabbit(snake->body.front());

    Game * game = Game::get();

    Dir dir_cur = snake -> dir;
    char next_p_cur = game->check_place_snake(snake->next_position(dir_cur, snake->body.front()));
    int next_cur = r.distance(snake->next_position(dir_cur, snake->body.front()));


    bool ok = false;



    if(r != Coord(0, 0)){
        int now = r.distance(snake->body.front());

        for(auto p : d)
        {
            snake->dir = p;
            char next_p = game->check_place_snake(snake->next_position(p, snake->body.front()));
            int next = r.distance(snake->next_position(p, snake->body.front()));
            if(next < now && (next_p == ' ' || next_p == 'r'))
            {
                if (next == next_cur && (next_p_cur == ' ' || next_p_cur == 'r'))
                {
                    snake -> dir = dir_cur;
                }
                ok = true;
                break;
            }
        }
    }

    if(!ok)
        for(auto p : d)
        {
            snake->dir = p;
            Coord c = snake->next_position(p, snake->body.front());
            if(game->check_place_snake(c) == ' ')
            {
                //snake->dir = p;
                break;
            }
        }
}
