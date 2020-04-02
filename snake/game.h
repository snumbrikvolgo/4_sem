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
                return std::abs(first - c.first) - std::abs(second - c.second);
            };
};

class Game;
class Snake{
public:
        enum Direction{
            UP,
            DOWN,
            RIGHT,
            LEFT,
            BODY,
            NONE,
        };

        explicit Snake(Game&);

        Snake(const Snake&) = delete;
        Snake& operator=(const Snake&) = delete;
        void set_direction(enum Direction d) {dir = d;}

        Coord next();
        void move(std::list<Coord>& rabbits);

        bool stopped;
        Direction dir;
        int brand;
        std::list<Coord> body;
protected:
        Game& game;
};

struct Segment : Coord {
        Segment(const Coord& c, int b, Snake::Direction d)
                : Coord(c), brand(b), dir(d){}
        int brand;
        Snake::Direction dir;
};
struct Rabbit: Coord, std::optional<int>{
        Rabbit(const Coord& c, const std::optional<int>& d = std::nullopt)
            :Coord(c), std::optional<int>(d) {}
};

class Game {
public:
    enum {
        TICK = 500, //milliseconds game tick
        RABBITS_CHANCE = 20,
        MAX_RABBITS = 10,
    };

    Game() {
        std::cout << "Game class creates\n" << std::endl;
    };
    void add(Snake& s);
    void move();
    void draw();

    Coord randxy();

    bool is_clear(Coord, bool skip_rabbits = false);
    std::optional<Coord> rabbit_near(Coord);
private:
        std:: list<std::reference_wrapper<Snake>> snakes;
        std::list<Coord> rabbits;
};
