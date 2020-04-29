#ifndef Gui_hpp
#define Gui_hpp

#include <stdio.h>

#include "ui.h"
#include "game.h"

#include <termios.h>

#include <SFML/Graphics.hpp>


const int CELL_SIZE = 30;


class Gui : public Ui {
public:
    Gui();
    ~Gui();


    sf::RenderWindow window;
    //Keypressable * onkey_delegater;

    //void snakepainter(Coord c, Dir d, Hum h);
    void rabbitpainter(const Coord& c);
    void snakepainter(const Coord& s, const Dir& dir, int color);

    void draw();
    void run(Game* g);

    void setcolor(int color);
    void gotoxy(int x, int y); //

    void cls(); //
    void winch();

    int winx() const { return x; }
    int winy() const { return y; }

    bool getkey(long time);
    void painter(int brand, int score);

    void Xline(int y);
    void Yline(int x);

private:
    struct termios old;

    sf::Texture t_ground;
    sf::Texture t_bort;
    sf::Texture t_body;
    sf::Texture t_head;
    sf::Texture t_apple;
    sf::Texture t_head_l;

    sf::Texture t_head_h;
    sf::Texture t_body_h;
    sf::Texture t_head_l_h;

    sf::Sprite ground;
    sf::Sprite bort;
    sf::Sprite body;
    sf::Sprite head;
    sf::Sprite apple;
    sf::Sprite head_l;

    sf::Sprite head_h;
    sf::Sprite body_h;
    sf::Sprite head_l_h;
};



#endif /* Gui_hpp */
