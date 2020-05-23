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

    void rabbitpainter(const Coord& c);
    void snakepainter(const Coord& s, const Dir& dir, int color);

    void draw();
    void run(Game* g);

    void setcolor(int color);
    void gotoxy(int x, int y);
    void cls();
    void winch();

    int winx() const { return x; }
    int winy() const { return y; }

    int getkey(long time);
    void painter(int brand, int score);

    void Xline(int y);
    void Yline(int x);

private:
    struct termios old;

    sf::Texture t_ground;
    sf::Texture t_bort;
    sf::Texture t_body;
    sf::Texture t_head;
    sf::Texture t_mush;
    sf::Texture t_head_l;

    sf::Texture t_head_h;
    sf::Texture t_body_h;
    sf::Texture t_head_l_h;

    sf::Texture t_head_2;
    sf::Texture t_body_2;
    sf::Texture t_head_l_2;

    sf::Sprite ground;
    sf::Sprite bort;
    sf::Sprite body;
    sf::Sprite head;
    sf::Sprite mush;
    sf::Sprite head_l;

    sf::Sprite head_h;
    sf::Sprite body_h;
    sf::Sprite head_l_h;

    sf::Sprite head_2;
    sf::Sprite body_2;
    sf::Sprite head_l_2;
    
    sf::Font font;
    sf::Text text;
};
