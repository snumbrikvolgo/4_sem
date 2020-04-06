#include <stdio.h>

#include "control.h"

class AI : public Control
{
public:
    AI(Snake * s);
    ~AI();

    void OnMove();

    Snake * snake;
};
