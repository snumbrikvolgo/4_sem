#include <memory>
#include <cstdio>
#include <iostream>
#include "ui.h"
#include "game.h"

int main() {

  srand(time(NULL));

  std::unique_ptr<Ui> v(Ui::get("tty"));
  if (!v) {
    fprintf(stderr, "Cannot init UI\n");
    return 0;
  }

  Game * g = Game::get();
  Snake* s = new Snake();

  g ->add(s);
  //g -> add(s);
  v -> set_model(g);
  v -> run();

 // while(1);

  //Human h(g);
  //Robot s1(g), s2(g), s3(g);

  //v->run(g);

}
