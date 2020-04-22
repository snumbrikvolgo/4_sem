#pragma once
#include <termios.h>
#include <sys/ioctl.h>
#include <vector>
#include "ui.h"
#include "game.h"


class Tty : public Ui {
public:

  Tty();
  ~Tty();

  int winx() const { return x; }
  int winy() const { return y; }

  void run(Game* g);
  //void quit();

  //void on_key(event_fn fn);
  //void on_timer(int t, timer_fn fn);

  void snakepainter(const Coord& s, const Dir& d);
  void rabbitpainter(const Coord&);
  void painter(int brand, int score);

  void draw();
  void cls(); //

  void putc(int x, int y, char c); //

  void hline(int x, int y, int len); // horizontal line
  void vline(int x, int y, int len); // vertical line

  void setcolor(int color);
  void gotoxy(int x, int y); //
  //bool read_event(); // read key
  // terminal
  //void init_tty(int echo);
  //void fini_tty();
  void winch();
  //static void handler(int a = 0);

private:
  bool running;
  struct termios old;
  //Game* game;

  //std::vector<event_fn> events;
  //std::vector<std::pair<int, timer_fn>> timers;
};
