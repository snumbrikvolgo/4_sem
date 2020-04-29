#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <fstream>
#include <unistd.h>

//using namespace std::placeholders;

#include "gui.h"
#include "game.h"

using namespace std::placeholders;
void Gui::winch()
{
    sf::Vector2u size = window.getSize();
//    ioctl(1, TIOCGWINSZ, &size);
//    x = 101;
//    y = 101;
    x = size.x / CELL_SIZE;
    y = size.y / CELL_SIZE;
}

Gui::Gui()
{
    window.create(sf::VideoMode(2700, 1500), "Snake", sf::Style::Fullscreen);
    winch();


    t_bort.loadFromFile("/Users/yaroslav/Desktop/Proga/Snake2.0/Snake2.0/bort.jpg");
    bort.setTexture(t_bort);

    t_ground.loadFromFile("/Users/yaroslav/Desktop/Proga/Snake2.1/Snake2.1/Bacground.png");
    ground.setTexture(t_ground);

    t_head.loadFromFile("/Users/yaroslav/Desktop/Proga/Snake2.0/Snake2.0/head.png");
    head.setTexture(t_head);

    t_head_l.loadFromFile("/Users/yaroslav/Desktop/Proga/Snake2.0/Snake2.0/head_l.png");
    head_l.setTexture(t_head_l);

    t_body.loadFromFile("/Users/yaroslav/Desktop/Proga/Snake2.0/Snake2.0/ body.png");
    body.setTexture(t_body);

    t_apple.loadFromFile("/Users/yaroslav/Desktop/Proga/Snake2.0/Snake2.0/apple.png");
    apple.setTexture(t_apple);

    t_head_h.loadFromFile("/Users/yaroslav/Desktop/Proga/Snake2.0/Snake2.0/HH.png");
    head_h.setTexture(t_head_h);

    t_head_l_h.loadFromFile("/Users/yaroslav/Desktop/Proga/Snake2.0/Snake2.0/HL.png");
    head_l_h.setTexture(t_head_l_h);

    t_body_h.loadFromFile("/Users/yaroslav/Desktop/Proga/Snake2.0/Snake2.0/HB.png");
    body_h.setTexture(t_body_h);
}

Gui::~Gui()
{
    //window.clear();
    //printf("Good bye\n");
}
void Gui::rabbitpainter(const Coord& c)
{
    apple.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
    window.draw(apple);
}

void Gui::snakepainter(const Coord& c, const Dir& dir, int color)
{
    //Gotoxy(c.first, c.second);
    //putchar("^V><*"[d]);

    switch (dir) {
        case UP:
            if (color == 0) {
                head_h.setTextureRect(sf::IntRect(0, 0, 30, 30));
                head_h.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(head_h);
            }
            else {
                head.setTextureRect(sf::IntRect(0, 0, 30, 30));
                head.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(head);
            }
            return;

        case DOWN:
            if (color == 0) {
                head_h.setTextureRect(sf::IntRect(0, 30, 30, -30));
                head_h.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(head_h);
            }
            else {
                head.setTextureRect(sf::IntRect(0, 30, 30, -30));
                head.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(head);
            }
            return;

        case LEFT:
            if (color == 0) {
                head_l_h.setTextureRect(sf::IntRect(0, 0, 30, 30));
                head_l_h.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(head_l_h);
            }
            else {
                head_l.setTextureRect(sf::IntRect(0, 0, 30, 30));
                head_l.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(head_l);
            }
            return;

        case RIGHT:
            if (color == 0) {
                head_l_h.setTextureRect(sf::IntRect(30, 0, -30, 30));
                head_l_h.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(head_l_h);
            }
            else {
                head_l.setTextureRect(sf::IntRect(30, 0, -30, 30));
                head_l.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(head_l);
            }
            return;

        default:
            if (color == 0) {
                body_h.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(body_h);
            }
            else {
                body.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
                window.draw(body);
            }
            return;
    }


}
void Gui::draw()
{
    winch();

    window.clear();

    for(int i = 0; i < y; i++)
        for(int j = 0; j < x; j ++) {
            ground.setPosition(j * CELL_SIZE, i * CELL_SIZE);
            window.draw(ground);
        }

        Xline(0);
        Xline(winx() - 1);

        Yline(0);
        Yline(winy() - 1);

    //Gotoxy(minx()/2, miny()/2);

    game->paint(std::bind(&Ui::snakepainter, this, _1, _2, _3), std::bind(&Ui::rabbitpainter, this, _1),  std::bind(&Ui::painter, this, _1, _2));

    //fflush(stdout);
}


void Gui::Xline(int y)
{
    //Gotoxy(0, y);
    for (int i = 0; i < winx(); i ++)
    {
        //Gotoxy(i, y);
        bort.setPosition(i * CELL_SIZE, y * CELL_SIZE);
        window.draw(bort);
        //printf("#");
    }
}


void Gui::Yline(int x)
{
    for (int i = 1; i <= winy(); i ++)
    {
        bort.setPosition(x * CELL_SIZE, i * CELL_SIZE);
        window.draw(bort);
    }

}

void Gui::run(Game* g)
{
    //printf("Hello, world. Snake\n");
    game = g;
    char c;
    draw();

    struct pollfd arr;
    struct timespec start_time, finish_time, worktime;

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }


        struct timespec start_time, finish_time, worktime;
        clock_gettime(CLOCK_REALTIME,  &start_time);
        bool suks = getkey((long)ontime_delegater.front().first);
        clock_gettime(CLOCK_REALTIME,  &finish_time);

        worktime.tv_sec = finish_time.tv_sec - start_time.tv_sec;
        worktime.tv_nsec = finish_time.tv_nsec - start_time.tv_nsec;
        int d = (int)(worktime.tv_sec * 1000) + (int)(worktime.tv_nsec / 1000000);
        //printf("d = %d\n", d );
        if(c == 'q')    return;


        for(int i = 0; i < ontime_delegater.size(); i ++) {
            std::pair<long, timeontable> a = ontime_delegater.front();
            ontime_delegater.pop_front();
            a.first -= d;
            ontime_delegater.push_back(a);
        }

        for(int i = 0; i < ontime_delegater.size(); i ++) {
            std::pair<long, timeontable> a = ontime_delegater.front();
            ontime_delegater.pop_front();

            if(a.first <= 0) {
                a.second();
            }

            else ontime_delegater.push_back(a);
        }

        draw();
        window.display();
    }
}

void Gui::painter(int brand, int score){}

bool Gui::getkey(long time)
{
    sf::Clock clock;
    sf::Time timer = sf::microseconds(1000);
    clock.restart();
    timer = clock.getElapsedTime();
    char c;

    sf::Event event;

    while (timer.asMicroseconds() / 1000 < time) {

//        if (event.type == sf::Event::KeyPressed)
//        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                c = 'd';
                if(onkey_delegater->onkey(c))
                return 1;
            }
//        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            c = 'a';
            if(onkey_delegater->onkey(c))
            return 1;
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            c = 'w';
            if(onkey_delegater->onkey(c))
            return 1;
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            c = 's';
            if(onkey_delegater->onkey(c))
            return 1;
        }

        timer = clock.getElapsedTime();
    }

    return 0;
}
