#pragma once
#include "game.h"
#include <poll.h>
#include <time.h>

using timeontable = std::function<void()>;
//using event_fn = std::function<void(int)>;
//using timer_fn = std::function<void(void)>;

class Ui {
public:

  enum {
    KEY_UP = 1000,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
  };

  std::list <std::pair < long, timeontable>> ontime_deligater;
  static Ui* get(const char* item = NULL); // if call get() then item = NULL

  virtual int winx() const = 0;
  virtual int winy() const = 0;

  //virtual void run(Game&) = 0;
  virtual void draw() = 0;
  //virtual void quit() = 0;

  virtual ~Ui() = 0;

  void setontimer(struct timespec timeout, timeontable t)
    {
        std::pair <long , timeontable> n;

        n.first = timeout.tv_nsec / 1000000 + timeout.tv_sec * 1000;
        n.second = t;

        //if(ontime_deligater.front().first >= n.first) ontime_deligater.push_front(n);
        ontime_deligater.push_back(n);
    }

  //virtual void on_key(event_fn fn) = 0;
  //virtual void on_timer(int, timer_fn fn) = 0;

  virtual void snakepainter(const Coord& s, const Dir& d) = 0;
  virtual void rabbitpainter(const Coord&) = 0;
  // score
  virtual void painter(int, int) = 0;
  virtual void winch() = 0;
  virtual void run() = 0;

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
