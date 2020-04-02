#include <memory>
#include <cstdio>
#include <iostream>
#include "ui.h"
#include "game.h"

int main() {

  std::unique_ptr<Ui> v(Ui::get("tty"));
  if (!v) {
    fprintf(stderr, "Cannot init UI\n");
    return 0;
  }
  v -> draw();
  while (1);


  //Game g;
  //Human h(g);
  //Robot s1(g), s2(g), s3(g);

  //v->run(g);

}
