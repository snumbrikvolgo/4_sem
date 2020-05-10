#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include "gui.h"
#include "game.h"

using namespace std::placeholders;

void Gui::winch()
{
    sf::Vector2u size = window.getSize();

    x = size.x / CELL_SIZE;
    y = size.y / CELL_SIZE;
}

Gui::Gui()
{
    window.create(sf::VideoMode(1920,1080), "Snake");
    winch();

    font.loadFromFile("fonts/CyrilicOld.TTF");
    text.setFont(font);
    text.setCharacterSize(40);


    t_bort.loadFromFile("./images/bort.jpg");
    bort.setTexture(t_bort);

    t_ground.loadFromFile("./images/grass.png");
    ground.setTexture(t_ground);


    t_head.loadFromFile("./images/head.png");
    head.setTexture(t_head);

    t_head_l.loadFromFile("./images/head_l.png");
    head_l.setTexture(t_head_l);

    t_body.loadFromFile("./images/body.png");
    body.setTexture(t_body);

    t_mush.loadFromFile("./images/mush.png");
    mush.setTexture(t_mush);

    t_head_h.loadFromFile("./images/HH.png");
    head_h.setTexture(t_head_h);

    t_head_l_h.loadFromFile("./images/HL.png");
    head_l_h.setTexture(t_head_l_h);

    t_body_h.loadFromFile("./images/HB.png");
    body_h.setTexture(t_body_h);
}

Gui::~Gui()
{
    window.clear();
    printf("Pokedova\n");
}
void Gui::rabbitpainter(const Coord& c)
{
    mush.setPosition(c.first * CELL_SIZE, c.second * CELL_SIZE);
    window.draw(mush);
}

void Gui::snakepainter(const Coord& c, const Dir& dir, int color)
{
    switch (dir) {
        case DOWN:
            if (color == 5) {
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

        case UP:
            if (color == 5) {
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
            if (color == 5) {
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
            if (color == 5) {
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
            if (color == 5) {
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
    text.setFillColor(sf::Color::Black);
    text.setString("Score : ");
    text.setPosition(0,0);


    Xline(0);
    Xline(winy());


    Yline(0);
    Yline(winx() - 1);
    window.draw(text);

    game->paint(std::bind(&Ui::snakepainter, this, _1, _2, _3), std::bind(&Ui::rabbitpainter, this, _1),  std::bind(&Ui::painter, this, _1, _2));

}


void Gui::Xline(int y)
{
    for (int i = 0; i <= winx(); i ++)
    {
        bort.setPosition(i * CELL_SIZE, y * CELL_SIZE);
        window.draw(bort);
    }
}


void Gui::Yline(int x)
{
    for (int i = 0; i <= winy(); i ++)
    {
        bort.setPosition(x * CELL_SIZE, i * CELL_SIZE);
        window.draw(bort);
    }

}

void Gui::run(Game* g)
{
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
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Q)
                    window.close();
        }

        struct timespec start_time, finish_time, worktime;
        clock_gettime(CLOCK_REALTIME,  &start_time);
        int success = getkey((long)ontime_delegater.front().first);
        clock_gettime(CLOCK_REALTIME,  &finish_time);

        worktime.tv_sec = finish_time.tv_sec - start_time.tv_sec;
        worktime.tv_nsec = finish_time.tv_nsec - start_time.tv_nsec;
        int d = (int)(worktime.tv_sec * 1000) + (int)(worktime.tv_nsec / 1000000);


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

void Gui::painter(int brand, int score)
{

    if (5 == score)
        text.setFillColor(sf::Color::Red);
    else if (8 == score)text.setFillColor(sf::Color::Green);
    else text.setFillColor(sf::Color::White);

    std::ostringstream p;
    p << brand;
    text.setString( p.str());
    text.setPosition(30*(score + 1), 5);
    window.draw(text);
    text.setFillColor(sf::Color::Transparent);
    text.setPosition(0, 0);

}

int Gui::getkey(long time)
{
    sf::Clock clock;
    sf::Time timer = sf::microseconds(1000);
    clock.restart();
    timer = clock.getElapsedTime();
    char c;

    sf::Event event;

    while (timer.asMicroseconds() / 1000 < time) {

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            c = 'd';
            if(onkey_delegater->onkey(c))
            return 1;
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            c = 'a';
            if(onkey_delegater->onkey(c))
            return 1;
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            c = 'q';
            return 0;
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            c = 's';
            if(onkey_delegater->onkey(c))
            return 1;
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            c = 'w';
            if(onkey_delegater->onkey(c))
            return 1;
        }

        timer = clock.getElapsedTime();
    }

    return 0;
}
