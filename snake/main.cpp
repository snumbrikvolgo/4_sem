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

int main() {
  srand(time(NULL));

  std::unique_ptr<Ui> v(Ui::get("gui"));
  if (!v) {
    fprintf(stderr, "Cannot init UI\n");
    return 0;
  }

  Game * g = Game::get();
  Snake* s = new Snake();
  Human h(s);

  Snake * s2 = new Snake();
  AI ai(s2);

  g -> add(s);
  g -> add(s2);
  v -> set_model(g);
  v -> draw();
  v -> run(g);
}
