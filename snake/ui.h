#pragma once
#include "game.h"

class Ui { // user interface class
public:
  //using event_fn = std::function<void(int)>;
  //using timer_fn = std::function<void(void)>;
  enum {
    KEY_UP = 1000,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
  };

  static Ui* get(const char* item = NULL); // if call get() then item = NULL

  virtual int winx() const = 0;
  virtual int winy() const = 0;

  //virtual void run(Game&) = 0;
  virtual void draw() = 0;
  //virtual void quit() = 0;

  virtual ~Ui() = 0;

  //virtual void on_key(event_fn fn) = 0;
  //virtual void on_timer(int, timer_fn fn) = 0;

  //All
  //virtual void painter() = 0;
  // snake
  virtual void painter(const Segment&) = 0;
  //rabbit
  virtual void painter(const Rabbit&) = 0;
  // score
  virtual void painter(int, int) = 0;
  virtual void winch() = 0;

protected:
  Ui() = default;

private:
  static Ui* instance;
};
