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
        explicit Snake();
        Snake(const Snake& s):dir(s.dir), body(s.body){}

        Coord next_position(Dir d, Coord a);
        void move();

        Snake& operator=(const Snake & s){
            dir = s.dir;
            body = s.body;
            return * this;
        }
        void set_direction(Dir d);

        bool alive;
        Dir dir;
        int brand;
        std::list<Coord> body;
protected:
};

struct Segment : Coord {
        Segment(const Coord& c, int b, Dir d)
                : Coord(c), brand(b), dir(d){}
        int brand;
        Dir dir;
};
// struct Rabbit: Coord, std::optional<int>{
//         Rabbit(const Coord& c, const std::optional<int>& d = std::nullopt)
//             :Coord(c), std::optional<int>(d) {}
// };

using SnakePainter = std::function<void(Coord, Dir)>;
using RabbitPainter = std::function<void(Coord)>;

class Game {
public:
    enum {
        RABBITS_CHANCE = 20,
        MAX_RABBITS = 20,
    };

    Game();
    void add(Snake* s);
    void move();
    void paint(SnakePainter ps, RabbitPainter pr);

    void rabbit_generate();
    bool check_place(Coord c);
    char check_place_snake(Coord c);
    Coord nearest_rabbit(Coord c);
    Coord get_free_coord();
    void kill_rabbit(Coord c);

    static Game * get();
    static Game * inst;

private:

    std::list<Snake*> snakes;
    std::list<Coord>  rabbits;
};
