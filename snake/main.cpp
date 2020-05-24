#include <memory>
#include <cstdio>
#include <string>
#include <iostream>
#include "ui.h"
#include "game.h"
#include "control.h"
#include "human.h"
#include "tui.h"
#include "gui.h"
#include "AI.h"

int main(int argc, char* argv[]) {
  srand(time(NULL));
  const char* name = "tty";

  if (argc != 1)
  {
      name = argv[1];
  }

  std::unique_ptr<Ui> v(Ui::get(name));
  if (!v) {
    fprintf(stderr, "Cannot init UI\n");
    return 0;
  }

  Game * g = Game::get();
  Snake* s = new Snake();
  Human h(s);

  Snake * s2 = new Snake();
  AI ai_2(s2, 'd');

  Snake * s3 = new Snake();
  AI ai_3(s3, 'c');

  g -> add(s);
  g -> add(s2);
  g -> add(s3);
  v -> run(g);

  v.reset();
  delete g;
  delete s;
  delete s2;
  delete s3;
}
