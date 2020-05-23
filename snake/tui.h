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
  void snakepainter(const Coord& s, const Dir& dir, int color);
  void rabbitpainter(const Coord&);
  void painter(int brand, int score);

  void draw();
  void cls();

  void putc(int x, int y, char c);
  void hline(int x, int y, int len);
  void vline(int x, int y, int len);

  void setcolor(int color);
  void gotoxy(int x, int y);
  void winch();

private:
  bool running;
  struct termios old;
};
