#pragma once
#include "human.h"
#include "game.h"
#include <poll.h>
#include <time.h>
#include <tuple>

using timeontable = std::function<void()>;

class AI;

class Ui {
public:
    
  Human* onkey_delegater;
  AI * AI_delegater;
  AI * AI_delegater_clever;

  void set_on_AI(AI * ai, char manner)
    {
        if (manner == 'd')
            AI_delegater = ai;
        else AI_delegater_clever = ai;
    }

  void set_on_key(Human* s)
   {
       onkey_delegater = s;
   }


  long make_time(struct timespec timeout)
  {
      return timeout.tv_nsec / 1000000 + timeout.tv_sec * 1000;
  }
  std::list <std::tuple<long, long, timeontable>> ontime_delegater;

  static Ui* get(const char* item = NULL);

  virtual int winx() const = 0;
  virtual int winy() const = 0;

  virtual void draw() = 0;

  virtual ~Ui() = 0;

  void set_on_timer(struct timespec timeout, struct timespec probe, timeontable t)
    {
        long first = make_time(timeout);
        long second = make_time(probe);

        ontime_delegater.push_back(std::make_tuple(first,second,t));
    }

  virtual void snakepainter(const Coord& s, const Dir& d, int color) = 0;
  virtual void rabbitpainter(const Coord&) = 0;
  virtual void painter(int, int) = 0;
  virtual void winch() = 0;
  virtual void run(Game* g) = 0;

  void set_model(Game* g)
  {
      game = g;
  }

  Game* game;

  Ui() {};
  int x;
  int y;

private:
  static Ui* instance;
};
