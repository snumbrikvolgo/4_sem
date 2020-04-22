#pragma once
#include "key.h"
#include "game.h"
#include <poll.h>
#include <time.h>

using timeontable = std::function<void()>;

class AI;

class Ui {
public:

  enum {
    KEY_UP = 1000,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
  };

  Key* onkey_delegater;
  AI * AI_delegater;

  void set_on_AI(AI * ai)
    {
        AI_delegater = ai;
    }

  void set_on_key(Key* key)
   {
       onkey_delegater = key;
   }

  std::list <std::pair < long, timeontable>> ontime_delegater;
  static Ui* get(const char* item = NULL);

  virtual int winx() const = 0;
  virtual int winy() const = 0;

  virtual void draw() = 0;

  virtual ~Ui() = 0;

  void set_on_timer(struct timespec timeout, timeontable t)
    {
        std::pair <long , timeontable> n;
        n.first = timeout.tv_nsec / 1000000 + timeout.tv_sec * 1000;
        n.second = t;
        ontime_delegater.push_back(n);
    }

  virtual void snakepainter(const Coord& s, const Dir& d, int color) = 0;
  virtual void rabbitpainter(const Coord&) = 0;
  // score
  virtual void painter(int, int) = 0;
  virtual void winch() = 0;
  virtual void run(Game* g) = 0;

  void set_model(Game* g)
  {
      game = g;
  }

  Game* game;

protected:
  Ui() = default;
  int x;
  int y;

private:
  static Ui* instance;
};
