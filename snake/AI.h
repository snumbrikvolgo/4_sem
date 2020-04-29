#include <stdio.h>

#include "control.h"

class AI : public Control
{
public:
    AI(Snake * s);
    ~AI();

    void on_move();

    Snake * snake;
};
