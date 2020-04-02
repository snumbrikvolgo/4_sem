#include "tui.h"
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
void Tty::winch()
{
    ioctl(1, TIOCGWINSZ, &ws);
}
Tty::Tty() {
  //init_tty(0);
  //winch();
  ioctl(0, TIOCGWINSZ, &ws);
  setvbuf(stdout, NULL, _IONBF, 0);
}

Tty::~Tty() {
printf("bye!\n");
  cls();
  //fini_tty();
  setvbuf(stdout, NULL, _IOLBF, 0);
  printf("bye!\n");
}

void Tty::cls() {
  printf("\e[H\e[J\e[m");
}

void Tty::gotoxy(int x, int y) {
  printf("\e[%d;%dH", ws.ws_row - y, x + 1);
}

void Tty::hline(int x, int y, int len) // horizontal line
{
    for(int i = x; i < x + len; ++i)
    {
        gotoxy(i, y);
        printf("*");
    }
}

void Tty::vline(int x, int y, int len) // vertical line
{
    for(int i = y; i < y + len; ++i)
    {
        gotoxy(x, i);
        printf("*");
    }
}

void Tty::setcolor(int c) {
  printf("\e[%dm", c ? c+30 : 0);
}
void Tty::painter(int brand, int score){
    gotoxy(10*brand, 0);
    setcolor(brand);
    printf(" %d ", score);
    setcolor(0);
    gotoxy(0,0);
}
void Tty::painter(const Segment& s){

    setcolor(s.brand);
    putc(s.first, s.second, "^v><#"[s.dir]);
    setcolor(0);
    gotoxy(0,0);
}
void Tty::painter(const Rabbit& s){

    putc(s.first, s.second, '@');
    setcolor(0);
    gotoxy(0,0);
}
void Tty::draw()
{
    winch();
    cls();
    printf("\ec");
    vline(0,0,winy());
    hline(0,0, winx());
    vline(winx() - 1,0,winy());
    hline(0,winy() - 1, winx());
    printf("\e[1m\e[%d;%dH\e[31mR\e[33mA\e[32mI\e[36mN\e[34mB\e[35mO\e[37mW\e[5m!",
            winy()/2+1, winx()/2-3);
    gotoxy(3,0);
    printf(" Score: ");
    printf("kekus\n" );
    //fflush(stdout);
}
void Tty::putc(int x, int y, char c){};
