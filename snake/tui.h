#pragma once

#include <termios.h>
#include <sys/ioctl.h>
#include <vector>
#include "game.h"
#include "ui.h"

class Tty : public Ui {
public:
  Tty();
  ~Tty();

  int winx() const { return ws.ws_col; }
  int winy() const { return ws.ws_row; }

  //void run(Game&);
  //void quit();

  //void on_key(event_fn fn);
  //void on_timer(int t, timer_fn fn);

  void painter(const Segment&);
  void painter(const Rabbit&);
  void painter(int brand, int score);

  void draw();

public:
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
  void winch(); //windowchange

private:
  struct winsize ws;
  struct termios ttys;
  bool running;
  //Game* game;

  //std::vector<event_fn> events;
  //std::vector<std::pair<int, timer_fn>> timers;
};
