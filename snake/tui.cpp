#include "tui.h"
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>

using namespace std::placeholders;

static void handler(int a) {
    Ui::get() -> draw();
}

void Tty::winch()
{
    cls();
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws); //get win size, as resized signal sigwich

    x = ws.ws_col;
    y = ws.ws_row;
}

Tty::Tty()
{
  cls();
  winch();

  struct sigaction sa;
  sa.sa_handler = handler;
  sa.sa_flags = SA_RESTART;
  sigaction(SIGWINCH, &sa, NULL);

  struct termios a;
  tcgetattr(0, &a);
  old = a;
  cfmakeraw(&a);
  tcsetattr(0, TCSAFLUSH, &a);
}

Tty::~Tty()
{
  cls();
  game = NULL;
  tcsetattr(0, TCSAFLUSH, &old);
  //printf("CALLED DESTRUCTOR TTY\n" );
  printf("Pokedova!\n");

}

void Tty::cls()
{
  printf("\ec");
}

void Tty::gotoxy(int w, int h)
{
  printf("\e[%d;%dH", y - h, w+ 1);
}

void Tty::hline(int w, int h, int len)
{
    for(int i = w; i < w + len; ++i)
    {
        gotoxy(i, h);
        printf("*");
    }
}

void Tty::vline(int w, int h, int len)
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

void Tty::painter(int score, int brand)
{
    gotoxy(8*(brand + 1), 0);
    setcolor(brand);
    printf(" %d ", score);
    setcolor(0);
    gotoxy(0,0);
}

void Tty::snakepainter(const Coord& s, const Dir& dir, int color)
{
    setcolor(color);
    putc(s.first, s.second, "^v><#"[dir]);
    setcolor(0);
    gotoxy(0,0);
}

void Tty::rabbitpainter(const Coord& s)
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
    vline(winx() - 1,0,winy());
    hline(0,winy() - 1, winx());
    gotoxy(3,0);
    printf(" Score: ");
    game->paint(std::bind(&Ui::snakepainter, this, _1, _2, _3), std::bind(&Ui::rabbitpainter, this, _1), std::bind(&Ui::painter, this, _1, _2));
    fflush(stdout);
}

void Tty::putc(int x, int y, char c)
{
    gotoxy(x,y);
    putchar(c);
}
void Tty::run(Game* g)
{
    game = g;
    char c;
    draw();

    struct pollfd key;
    struct timespec start_time, finish_time, worktime;
    while(1)
    {
        key.fd = 0 ;
        key.events = POLLIN;

        clock_gettime(CLOCK_REALTIME,  &start_time);
        int n = poll(&key, 1, (int)std::get<0>(ontime_delegater.front()));
        clock_gettime(CLOCK_REALTIME,  &finish_time);

        if(n == 1) {
            read(key.fd, &c, 1);
            if(c == 'q')    return;
            onkey_delegater->onkey(c);
        }

        worktime.tv_sec = finish_time.tv_sec - start_time.tv_sec;
        worktime.tv_nsec = finish_time.tv_nsec - start_time.tv_nsec;
        int d = (int)(worktime.tv_sec * 1000) + (int)(worktime.tv_nsec / 1000000);

        for(auto& a: ontime_delegater) {
            std::get<0>(a) -= d;

            if(std::get<0>(a) <= 0) {
                std::get<0>(a) = std::get<1>(a);
                std::get<2>(a)();

            }
        }
    }
}
