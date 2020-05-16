#include <stdio.h>

#include "control.h"

class AI : public Control
{
public:
    AI(Snake * s, char manner);
    ~AI();

    void on_move_dumb();
    void on_move_clever();

    Snake * snake;
};
