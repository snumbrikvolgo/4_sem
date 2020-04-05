#include "tui.h"
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>

static void handler(int a) {
    Ui::get() -> draw();
}

void Tty::winch()
{
    cls();
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);

    x = ws.ws_col;
    y = ws.ws_row;
}

Tty::Tty()
{
  cls();
  std::cout << "HHUUUI\n" << std::endl;
  winch();
  //signal(SIGWINCH, handler);
  struct sigaction sa;
  sa.sa_handler = handler;
  sa.sa_flags = SA_RESTART;
  sigaction(SIGWINCH, &sa, NULL);

  struct termios a;
  tcgetattr(0, &a);
      old = a;
    cfmakeraw(&a);

    //int x = View::get()->x;
    tcsetattr(0, TCSAFLUSH, &a);

  //printf("%d %d\n", winx(), winy());
  //setvbuf(stdout, NULL, _IONBF, 0);
}

Tty::~Tty()
{
  tcgetattr(TCSAFLUSH, &old);
  cls();
  //fini_tty();
  //setvbuf(stdout, NULL, _IOLBF, 0);
  printf("bye!\n");
}

void Tty::cls()
{
  printf("\ec");
  //printf("\e[H\e[J\e[m");
}

void Tty::gotoxy(int w, int h)
{
  printf("\e[%d;%dH", y - h, w+ 1);
}

void Tty::hline(int w, int h, int len) // horizontal line
{
    for(int i = w; i < w + len; ++i)
    {
        gotoxy(i, h);
        printf("*");
    }
}

void Tty::vline(int w, int h, int len) // vertical line
{
    for(int i = h; i < h + len; ++i)
    {
        gotoxy(w, i);
        printf("*");
    }
}

void Tty::setcolor(int c)
{
  printf("\e[%dm", c ? c+30 : 0);
}

void Tty::painter(int brand, int score)
{
    gotoxy(10*brand, 0);
    setcolor(brand);
    printf(" %d ", score);
    setcolor(0);
    gotoxy(0,0);
}

void Tty::painter(const Segment& s)
{
    setcolor(s.brand);
    putc(s.first, s.second, "^v><#"[s.dir]);
    setcolor(0);
    gotoxy(0,0);
}

void Tty::painter(const Rabbit& s)
{
    putc(s.first, s.second, '@');
    setcolor(0);
    gotoxy(0,0);
}

void Tty::draw()
{
    winch();
    cls();
    vline(0,0,winy());
    hline(0,0, winx());
    Coord r;
    r.first = 5;
    r.second  = 6;

    //struct Rabbit rab (r);
    painter(r);
    r.first = 10;
    r.second  = 17;
    Segment f(r, 5, LEFT );
    painter(f);
    vline(winx() - 1,0,winy());
    hline(0,winy() - 1, winx());
    //printf("\e[1m\e[%d;%dH\e[31mR\e[33mA\e[32mI\e[36mN\e[34mB\e[35mO\e[37mW\e[37m!",
    //          winy()/2+1, winx()/2-3);
    gotoxy(3,0);
    printf(" Score: ");
    //game -> paint();
    fflush(stdout);
}

void Tty::putc(int x, int y, char c)
{
    gotoxy(x,y);
    putchar(c);
}
void Tty::run()
{
    draw();
}
