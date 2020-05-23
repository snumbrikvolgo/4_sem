#pragma once
#include <iostream>
#include <list>
#include <utility>
#include <optional>
#include <functional>

struct Coord : std::pair<int,int> {
        using Base = std::pair<int,int>;
        using Base::Base;
        int distance(const Coord& c) const{
                return std::abs(first - c.first) + std::abs(second - c.second);
            };
};

enum Dir{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    BODY,
    NO,
};

class Game;

class Snake{
public:
        Snake();
        ~Snake();

        Coord next_position(Dir d, Coord a);
        void move();

        Snake& operator=(const Snake & s){
            dir = s.dir;
            body = s.body;
            return* this;
        }
        void set_direction(Dir d);

        bool alive;
        Dir dir;
        int brand;
        std::list<Coord> body;
        int snake_score;
};

using SnakePainter  = std::function<void(Coord, Dir, int)>;
using RabbitPainter = std::function<void(Coord)>;
using ScorePainter  = std::function<void(int, int)>;

class Game {
public:
    enum {
        MAX_RABBITS = 20,
    };
    Game();
    ~Game();
    void add(Snake* s);
    void move();
    void paint(SnakePainter ps, RabbitPainter pr, ScorePainter psc);

    void rabbit_generate();
    bool check_place(Coord c);
    char check_place_snake(Coord c);
    Coord nearest_rabbit(Coord c);
    Coord get_free_coord();
    void kill_rabbit(Coord c);

    static Game * get();
    static Game * inst;
    static int snake_number ;

private:

    std::list<Snake*> snakes;
    std::list<Coord>  rabbits;
};
